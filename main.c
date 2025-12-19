#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "scheduler.h"
#include "metrics.h"
#include "process.h"
#include "config.h"

/* Disable Gantt in stress mode */
int SHOW_GANTT = 1;

/* ---------------- Policy Struct ---------------- */
typedef struct {
    char name[20];
    float avg_wt;
    float avg_tat;
    float fairness;
    int starvation;
} Policy;

/* ---------------- Helpers ---------------- */

void reload_processes(Process p[], int *n) {
    *n = load_processes("processes.txt", p);
    if (*n <= 0) {
        printf("Failed to load processes\n");
        exit(1);
    }
}

void generate_random_processes(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].arrival = rand() % 10;
        p[i].burst = 1 + rand() % 10;
        p[i].priority = 1 + rand() % 5;
    }
}

/* ---------------- MAIN ---------------- */

int main(int argc, char *argv[]) {

    Process p[20];
    int n = load_processes("processes.txt", p);

    if (argc < 2) {
        printf("Usage:\n");
        printf("./scheduler fcfs | sjf | priority | rr <q> | all | --stress <runs>\n");
        return 1;
    }

    /* ---------------- SINGLE MODES ---------------- */

    if (strcmp(argv[1], "fcfs") == 0) {
        run_fcfs(p, n);
        print_metrics(p, n);
        return 0;
    }

    if (strcmp(argv[1], "sjf") == 0) {
        run_sjf(p, n);
        print_metrics(p, n);
        return 0;
    }

    if (strcmp(argv[1], "priority") == 0) {
        run_priority(p, n);
        print_metrics(p, n);
        return 0;
    }

    if (strcmp(argv[1], "rr") == 0 && argc == 3) {
        run_rr(p, n, atoi(argv[2]));
        print_metrics(p, n);
        return 0;
    }

    /* ---------------- ALL MODE ---------------- */

    if (strcmp(argv[1], "all") == 0) {

        float wt, tat;

        reload_processes(p, &n);
        run_fcfs(p, n);
        calculate_averages(p, n, &wt, &tat);
        printf("FCFS     -> Avg WT: %.2f  Avg TAT: %.2f\n", wt, tat);

        reload_processes(p, &n);
        run_sjf(p, n);
        calculate_averages(p, n, &wt, &tat);
        printf("SJF      -> Avg WT: %.2f  Avg TAT: %.2f\n", wt, tat);

        reload_processes(p, &n);
        run_sjf_preemptive(p, n);
        calculate_averages(p, n, &wt, &tat);
        printf("SRTF     -> Avg WT: %.2f  Avg TAT: %.2f\n", wt, tat);

        reload_processes(p, &n);
        run_priority(p, n);
        calculate_averages(p, n, &wt, &tat);
        printf("PRIORITY -> Avg WT: %.2f  Avg TAT: %.2f\n", wt, tat);

        reload_processes(p, &n);
        run_rr(p, n, 2);
        calculate_averages(p, n, &wt, &tat);
        printf("RR(Q=2)  -> Avg WT: %.2f  Avg TAT: %.2f\n", wt, tat);

        return 0;
    }

    /* ---------------- STRESS MODE ---------------- */

    if (strcmp(argv[1], "--stress") == 0 && argc == 3) {

        int runs = atoi(argv[2]);
        int n = 10;

        Process base[20], temp[20];
        Policy fcfs = {"FCFS",0,0,0,0};
        Policy srtf = {"SRTF",0,0,0,0};
        Policy rr   = {"RR",0,0,0,0};
        Policy pr   = {"PRIORITY",0,0,0,0};

        srand(time(NULL));
        SHOW_GANTT = 0;

        for (int r = 0; r < runs; r++) {

            generate_random_processes(base, n);

            memcpy(temp, base, sizeof(Process)*n);
            run_fcfs(temp, n);
            calculate_averages(temp, n, &fcfs.avg_wt, &fcfs.avg_tat);
            fcfs.fairness += calculate_fairness(temp, n);

            memcpy(temp, base, sizeof(Process)*n);
            run_sjf_preemptive(temp, n);
            calculate_averages(temp, n, &srtf.avg_wt, &srtf.avg_tat);
            srtf.fairness += calculate_fairness(temp, n);

            memcpy(temp, base, sizeof(Process)*n);
            run_rr(temp, n, 2);
            calculate_averages(temp, n, &rr.avg_wt, &rr.avg_tat);
            rr.fairness += calculate_fairness(temp, n);
            rr.starvation += detect_starvation(temp, n, 15);

            memcpy(temp, base, sizeof(Process)*n);
            run_priority(temp, n);
            calculate_averages(temp, n, &pr.avg_wt, &pr.avg_tat);
            pr.fairness += calculate_fairness(temp, n);
            pr.starvation += detect_starvation(temp, n, 15);
        }

        /* Normalize */
        fcfs.avg_wt /= runs; fcfs.avg_tat /= runs; fcfs.fairness /= runs;
        srtf.avg_wt /= runs; srtf.avg_tat /= runs; srtf.fairness /= runs;
        rr.avg_wt   /= runs; rr.avg_tat   /= runs; rr.fairness   /= runs;
        pr.avg_wt   /= runs; pr.avg_tat   /= runs; pr.fairness   /= runs;

        Policy policies[4] = {fcfs, srtf, rr, pr};

        Policy best_wt = policies[0];
        Policy best_tat = policies[0];
        Policy best_fair = policies[0];
        Policy best_starve = policies[0];

        for (int i = 1; i < 4; i++) {
            if (policies[i].avg_wt < best_wt.avg_wt) best_wt = policies[i];
            if (policies[i].avg_tat < best_tat.avg_tat) best_tat = policies[i];
            if (policies[i].fairness < best_fair.fairness) best_fair = policies[i];
            if (policies[i].starvation < best_starve.starvation) best_starve = policies[i];
        }

        printf("\n===== BEST POLICY BY METRIC =====\n");
        printf("Best for Waiting Time     : %s\n", best_wt.name);
        printf("Best for Turnaround Time : %s\n", best_tat.name);
        printf("Best for Fairness        : %s\n", best_fair.name);
        printf("Best for Starvation      : %s\n", best_starve.name);

        return 0;
    }

    printf("Invalid command\n");
    return 0;
}
