#include <stdio.h>
#include "gantt.h"
#include "config.h"
static int g_pid[200];
static int g_time[200];
static int g_count = 0;
static int g_end_time = 0;

void gantt_reset() {
    g_count = 0;
}

void gantt_add(int pid, int time) {
    if (!SHOW_GANTT) return;
    g_pid[g_count] = pid;
    g_time[g_count] = time;
    g_count++;
}

void gantt_finish(int end_time) {
    if (!SHOW_GANTT) return;
    g_end_time = end_time;
}

void gantt_print() {
    if (!SHOW_GANTT) return;
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < g_count; i++)
        if (g_pid[i] == -1)
    printf(" IDLE |");
    else
        printf(" P%d |", g_pid[i]);


    printf("\n%d", g_time[0]);
    for (int i = 1; i < g_count; i++)
        printf("   %d", g_time[i]);

    printf("   %d\n", g_end_time);
}
