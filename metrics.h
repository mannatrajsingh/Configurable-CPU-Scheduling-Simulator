#ifndef METRICS_H
#define METRICS_H

#include "process.h"

void print_metrics(Process p[], int n);
void calculate_averages(Process p[], int n, float *avg_wt, float *avg_tat);
float calculate_fairness(Process p[], int n);
int detect_starvation(Process p[], int n, int threshold);

#endif
