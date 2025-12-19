#include <limits.h>
#include "scheduler.h"
#include "gantt.h"

void run_sjf_preemptive(Process p[], int n) {
    int time = 0;
    int completed = 0;
    int shortest = -1;
    int min_remaining;

    gantt_reset();

    /* Initialize remaining time */
    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    while (completed < n) {
        min_remaining = INT_MAX;
        shortest = -1;

        /* Pick process with smallest remaining time */
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time &&
                p[i].remaining > 0 &&
                p[i].remaining < min_remaining) {

                min_remaining = p[i].remaining;
                shortest = i;
            }
        }

        /* CPU idle */
if (shortest == -1) {
    gantt_add(-1, time);   // IDLE
    time++;
    continue;
}


        /* Execute for 1 unit */
        gantt_add(p[shortest].pid, time);
        p[shortest].remaining--;
        time++;

        /* Process finished */
        if (p[shortest].remaining == 0) {
            completed++;
            p[shortest].completion = time;
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
