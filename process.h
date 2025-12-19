#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    int arrival;
    int burst;
    int priority;

    int remaining;
    int completion;
    int waiting;
    int turnaround;
} Process;

#endif
