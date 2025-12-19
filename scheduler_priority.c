#include "scheduler.h"
#include "gantt.h"

void run_priority(Process p[], int n) {
    int time = 0, completed = 0;
    int done[n];
    gantt_reset();

    for (int i = 0; i < n; i++)
        done[i] = 0;

    while (completed < n) {
        int idx = -1, best = 9999;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }

if (idx == -1) {
    gantt_add(-1, time);
    time++;
    continue;
}

        gantt_add(p[idx].pid, time);

        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].turnaround = time - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;

        done[idx] = 1;
        completed++;
    }
gantt_finish(time);
    gantt_print();
}
