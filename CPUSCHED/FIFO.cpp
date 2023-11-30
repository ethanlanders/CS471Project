#include "FIFO.h"

// Function to perform First-In-First-Out (FIFO) Scheduling
void FIFO(std::vector<CPU_Process> processes)
{
    std::vector<CPU_Process> fifoProcess = processes;
    std::sort(fifoProcess.begin(), fifoProcess.end(), compareArrivalTime);

    /*  Declare variables   */

    // Number of processes we are working with
    int numOfProcesses = 0;

    // Total amount of time CPU is working on a process
    int totalCPUBurstTime = 0;
    
    // The extra time it takes for the CPU to complete a process
    int totalWaitingTime = 0;
    
    // Time between when a process arrives and when it completes
    int totalTurnaroundTime = 0;
    
    // Time it takes for the CPU to intially start working on a process
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
        numOfProcesses++;

        currentTime = endTime;
    }

    cout << "Statistics for FIFO Scheduling\n\n";
    calculations(numOfProcesses, currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);
}