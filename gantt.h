#ifndef GANTT_H
#define GANTT_H

void gantt_reset();
void gantt_add(int pid, int time);
void gantt_finish(int end_time);
void gantt_print();

#endif
