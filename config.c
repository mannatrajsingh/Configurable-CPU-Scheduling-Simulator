#include <stdio.h>
#include "config.h"

int load_processes(const char *file, Process p[]) {
    FILE *fp = fopen(file, "r");
    if (!fp) return -1;

    int i = 0;
    while (fscanf(fp, "%d %d %d %d",
                  &p[i].pid,
                  &p[i].arrival,
                  &p[i].burst,
                  &p[i].priority) == 4) {
        i++;
    }

    fclose(fp);
    return i;
}
