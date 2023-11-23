#include "FIFO.h"

// Function to perform First-In-First-Out (FIFO) Scheduling
void FIFO(std::vector<CPU_Process> processes)
{

    std::vector<CPU_Process> fifoProcess = processes;
    std::sort(fifoProcess.begin(), fifoProcess.end(), compareArrivalTime);

    // Declare variables

    int numOfProcesses = 541;
    // Local counter of number of completed processes
    int numOfCompletedProcesses = 0;
    // Total amount of time CPU is working on a process
    //      Idle time is elapsedTime - Burst time
    int totalCPUBurstTime = 0;
    // Extra Time it takes for cpu to complete a process
    //      Wait: (arrival + burst) - completed time
    int totalWaitingTime = 0;
    // Durration between When a process arrives till its completion
    int totalTurnaroundTime = 0;
    // Time it takes for cpu to intially start working on a process
    int totalResponseTime = 0;

    int currentTime = fifoProcess[0].arrivalTime;

    for (CPU_Process p : fifoProcess)
    {
        int startTime = std::max(currentTime, p.arrivalTime);
        int endTime = startTime + p.CPU_BurstLength;

        totalWaitingTime += startTime - p.arrivalTime;
        totalTurnaroundTime += endTime - p.arrivalTime;
        totalResponseTime += startTime - p.arrivalTime;
        totalCPUBurstTime += p.CPU_BurstLength;
        numOfCompletedProcesses++;

        currentTime = endTime;
    }

    cout << "Statistics for FIFO Scheduling\n\n";
    calculations(numOfCompletedProcesses, currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);
}