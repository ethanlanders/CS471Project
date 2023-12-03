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
As seen by the output results for all three scheduling algorithms, the average waiting time have similar values to the average response time.  The average turnaround time is the longest with fifo scheduler (______ CPU burst lengths), then the priority scheduler, and then the SJF scheduler has the shortest at ______.

The average waiting time is close in values for the fifo and priority scheduler with both around ______ CPU burst units while the SJF has a relatively short waiting time at ______ units. The SJF scheduler gives priority to processes that require less time to complete meaning by executing shorter jobs first, it reduces the average waiting time of processes in the ready queue which is why it has the shortest average waiting time amongst the three schedulers.

The throughput and CPU utilization also have similar values for all three since they are calculated using the same equations:

**Throughput** = total number of processes/total elapsed time

**CPU utilization** = total burst time/total elapsed time