#include "scheduler.h"
#include "gantt.h"

static int all_done(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        if (p[i].remaining > 0)
            return 0;
    }
    return 1;
}

void run_rr(Process p[], int n, int quantum) {
    int time = 0;
    gantt_reset();

    /* Initialize remaining time */
    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    while (!all_done(p, n)) {
        int executed = 0;

        for (int i = 0; i < n; i++) {

            if (p[i].remaining > 0 && p[i].arrival <= time) {
                executed = 1;

                gantt_add(p[i].pid, time);

                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    p[i].completion = time;
                }
            }
        }

        /* CPU idle */
        if (!executed) {
            gantt_add(-1, time);   // IDLE
            time++;
        }
    }

    /* Calculate metrics */
    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    gantt_finish(time);
    gantt_print();
}
