#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

void run_fcfs(Process p[], int n);
void run_sjf(Process p[], int n);
void run_priority(Process p[], int n);
void run_rr(Process p[], int n, int quantum);
void run_sjf_preemptive(Process p[], int n);

#endif
