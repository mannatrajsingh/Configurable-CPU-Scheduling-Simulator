#ifndef CONFIG_H
#define CONFIG_H

extern int SHOW_GANTT;
#include "process.h"

int load_processes(const char *file, Process p[]);

#endif
