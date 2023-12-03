# Project Problem 1:  CPU Scheduling
CS471, Old Dominion University, Fall 2023

## Authors
Ethan Landers<br>
Charles Milroy

## Description
This program will act as a CPU scheduler and handle scheduling 541 simulated processes using these scheduling algorithms: FIFO, SJF without preemption, Priority with preemption.

## Input file
The program takes an input text file titled "datafile.txt" that contains 541 processes with three columns: "Arrival time", "CPU burst length", and "priority".

## Compiling the program
The program can be compiled in Terminal by:
- Going to the CPUSCHED folder using the 'cd' command
- Running the command 'make'

## Running the program
The program can be run in Terminal by:
- Going to the CPUSCHED folder using the 'cd' command
- Running the command 'make test'

## Output
The output files have the following structure: "Output-[Scheduling Type].txt", such as:
- `Output-FIFOScheduling.txt`
- `Output-PriorityScheduling.txt`
- `Output-SJFScheduling.txt`

Each output file will have the following format and content:
```
Statistics for [Scheduling Type] Scheduling

Number of processes: ________
Total elapsed time (for the scheduler): ________
Throughput (Number of processes executed in one unit of CPU burst time): ________
CPU utilization: ________
Average waiting time (in CPU burst times): ________
Average turnaround time (in CPU burst times): ________
Average response time (in CPU burst times): ________
```

## Result's summary and explanation
**Disclaimer:** We met with the professor prior to completing this projet, and she stated that we should handle the whole input file instead of a specific number of processes, which is what the rubric states. 

The average waiting time and response time values were similar for SJF as well as for FIFO. On the other hand, priority had a higher average waiting time in comparison to its average response time. 

The average turnaround time is the longest with the priority scheduler (71.63 CPU burst lengths), then the SJF scheduler (63.03 CPU burst lengths), and then the FIFO scheduler (50.97 CPU burst lengths).

The average waiting time is the longest with the priority scheduler (50.26 CPU burst lengths), then the FIFO scheduler (41.66 CPU burst lengths), and then the SJF scheduler (29.60 CPU burst lengths).

Due to handling all 541 processes in the data file, the total elapsed time is the same for all three functions at 15688.  The throughput for each scheduling algorithm is the same at 0.0467912 as well as for CPU utilziation at 0.736996.

With a limit of 500 processes (following the rubric), the results are more varied: