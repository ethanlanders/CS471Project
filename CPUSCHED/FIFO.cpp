#include "FIFO.h"

bool compareArrivalTime(const CPU_Process& p1, const CPU_Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

// Function to perform First-In-First-Out (FIFO) Scheduling
void FIFO(std::vector<CPU_Process> processes)
{

std::vector<CPU_Process> fifoProcess = processes;
    std::sort(fifoProcess.begin(), fifoProcess.end(), compareArrivalTime);
    // Declare variables

    // Total time it takes to complete 500 proceeses
    int elapsedTime = 0;
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
//        // Wait for the next proccess if the current one has not arrived
//        if (p.arrivalTime > elapsedTime) // there is no need to add this condition here
//        {
//            totalCPUBurstTime += p.arrivalTime - elapsedTime;
//            elapsedTime = p.arrivalTime;
//        }
//
//        // Calculate completion time (time when the procsses finishes executing)
//        elapsedTime = p.arrivalTime + p.CPU_BurstLength;
//        numOfCompletedProcesses++;
//        totalWaitingTime += (p.arrivalTime + p.CPU_BurstLength) - elapsedTime;
//        totalTurnaroundTime += elapsedTime - p.arrivalTime;
//
//        // Calculate response time
//        int responseTime = elapsedTime - p.arrivalTime;
//        totalResponseTime += responseTime;
//
//        // Simulate the CPU's burst time
//        elapsedTime += p.CPU_BurstLength;
//
//        // Calculate total CPU burst time
//        totalCPUBurstTime += p.CPU_BurstLength;
//
//        // Increment the number of completed processes
//        numOfCompletedProcesses++;
//
//        // Exit the loop when 500 processes are completed
//        if (numOfCompletedProcesses >= 500)
//        {
//            break;
//        }



        int startTime = std::max(currentTime, p.arrivalTime);
        int endTime = startTime + p.CPU_BurstLength;

        totalWaitingTime += startTime - p.arrivalTime;
        totalTurnaroundTime += endTime - p.arrivalTime;
        totalResponseTime += startTime - p.arrivalTime;
        totalCPUBurstTime += p.CPU_BurstLength;

        currentTime = endTime;


    }

    cout << "\nStatistics for FIFO Scheduling\n\n";
    calculations(currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);
}