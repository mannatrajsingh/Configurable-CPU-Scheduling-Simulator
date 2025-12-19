# Configurable CPU Scheduling Simulator

A configurable CPU scheduling simulator written in C that implements and analyzes multiple operating system scheduling policies. The project focuses on correctness, fairness, starvation detection, and empirical performance comparison rather than only algorithm implementation.

---

## Features

- Implements multiple CPU scheduling algorithms:
  - First Come First Serve (FCFS)
  - Shortest Job First (SJF)
  - Shortest Remaining Time First (SRTF – preemptive)
  - Priority Scheduling
  - Round Robin (configurable time quantum)
- Gantt chart visualization with proper handling of idle CPU time
- Computes key scheduling metrics:
  - Average Waiting Time (WT)
  - Average Turnaround Time (TAT)
  - Fairness (standard deviation of waiting times)
  - Starvation detection
- Stress-testing mode to empirically compare scheduling policies on randomized workloads
- Modular design with Makefile-based build system

---

## Technologies Used

- Language: C
- Platform: Unix/Linux
- Build System: Makefile

---

## Project Structure

.
├── main.c # Command-line interface and control logic
├── scheduler.h # Scheduler function declarations
├── scheduler_fcfs.c # FCFS scheduling implementation
├── scheduler_sjf.c # Non-preemptive SJF scheduling
├── scheduler_sjf_preemptive.c # Preemptive SJF (SRTF)
├── scheduler_priority.c # Priority scheduling
├── scheduler_rr.c # Round Robin scheduling
├── metrics.c # Waiting time, turnaround time, fairness, starvation
├── metrics.h
├── gantt.c # Gantt chart visualization
├── gantt.h
├── process.h # Process data structure
├── config.c # Global configuration (e.g., Gantt toggle)
├── config.h
├── processes.txt # Input process list
├── Makefile
└── scheduler # Compiled executable


---

## Build Instructions



make clean
make


This generates the executable `scheduler`.

---

## Run Instructions

### Run individual scheduling policies


./scheduler fcfs
./scheduler sjf
./scheduler priority
./scheduler rr 2


### Run all policies with summary output


./scheduler all


### Run stress testing and policy analysis


./scheduler --stress 1000
