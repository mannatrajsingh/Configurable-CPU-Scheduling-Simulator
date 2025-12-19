#include <stdio.h>
#include "metrics.h"
#include <math.h>


float calculate_fairness(Process p[], int n) {
    float mean = 0;
    for (int i = 0; i < n; i++)
        mean += p[i].waiting;
    mean /= n;

    float variance = 0;
    for (int i = 0; i < n; i++) {
        float diff = p[i].waiting - mean;
        variance += diff * diff;
    }
    variance /= n;

    return sqrt(variance);   // standard deviation
}

int detect_starvation(Process p[], int n, int threshold) {
    int starving = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].waiting > threshold)
            starving++;
    }
    return starving;
}

void print_metrics(Process p[], int n) {
    float avg_wt = 0, avg_tat = 0;

    printf("\nPID AT BT PR CT TAT WT\n");

    for (int i = 0; i < n; i++) {
        printf("%d  %d  %d  %d  %d  %d  %d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].priority,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);

        avg_wt += p[i].waiting;
        avg_tat += p[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);
}
void calculate_averages(Process p[], int n, float *avg_wt, float *avg_tat) {
    float wt = 0, tat = 0;

    for (int i = 0; i < n; i++) {
        wt += p[i].waiting;
        tat += p[i].turnaround;
    }

    *avg_wt = wt / n;
    *avg_tat = tat / n;
}
