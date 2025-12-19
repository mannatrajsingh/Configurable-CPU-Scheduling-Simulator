# Configurable CPU Scheduling Simulator

A CPU scheduling simulator written in C that implements and analyzes multiple operating system scheduling policies. The project focuses on correctness, fairness, starvation analysis, and empirical performance comparison.

## Features
- Implements FCFS, SJF, SRTF (preemptive), Priority, and Round Robin scheduling
- Gantt chart visualization with proper handling of idle CPU time
- Computes waiting time, turnaround time, fairness, and starvation metrics
- Stress testing mode to empirically compare scheduling policies on randomized workloads
- Modular design with Makefile-based build

## Technologies Used
- C
- Unix/Linux
- Makefile

## Project Structure
- main.c – command-line interface
- scheduler_*.c – scheduling algorithms
- metrics.c / metrics.h – performance metrics
- gantt.c / gantt.h – Gantt chart visualization
- process.h – process data structure
- config.c / config.h – global configuration
- processes.txt – input process list
- Makefile

## Build Instructions
make clean
make


## Run Instructions
./scheduler fcfs
./scheduler sjf
./scheduler priority
./scheduler rr 2
./scheduler all
./scheduler --stress 1000
