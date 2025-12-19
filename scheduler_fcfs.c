#include "scheduler.h"
#include "gantt.h"

void run_fcfs(Process p[], int n) {
    int time = 0;
    gantt_reset();

    for (int i = 0; i < n; i++) {
if (time < p[i].arrival) {
    gantt_add(-1, time);          // CPU idle starts
    time = p[i].arrival;
}


        gantt_add(p[i].pid, time);   // CPU starts P[i]

        time += p[i].burst;

        p[i].completion = time;
        p[i].turnaround = time - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
    gantt_finish(time);
    gantt_print();
}
