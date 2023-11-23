#include "preemptive.h"

// Function to perform Preemptive Priority Scheduling
void preemptivePriority(vector<CPU_Process> &processes)
{
    std::vector<CPU_Process> sjfProcess = processes;
    std::sort(sjfProcess.begin(), sjfProcess.end(), compareArrivalTime);

    /*  Declare variables   */

    // Number of processes we are working with contained within datafile.txt
    int numOfProcesses = 541;
    
    // Local variable for the number of completed processes
    int numOfCompletedProcesses = 0;

    // Total amount of time CPU is working on a process
    int totalCPUBurstTime = 0;
    
    // The extra time it takes for the CPU to complete a process
    int totalWaitingTime = 0;
    
    // Time between when a process arrives and when it completes
    int totalTurnaroundTime = 0;
    
    // Time it takes for the CPU to intially start working on a process
    int totalResponseTime = 0;

    int currentTime = sjfProcess[0].arrivalTime;

    std::vector<int> readyIndices;
    int currentIndex = 0; // Keep track of the current process index

    while (currentIndex < processes.size() || !readyIndices.empty())
    {
        while (currentIndex < processes.size() && sjfProcess[currentIndex].arrivalTime <= currentTime)
        {
            readyIndices.push_back(currentIndex);
            currentIndex++;
        }

        if (readyIndices.empty())
        {
            currentTime = sjfProcess[currentIndex].arrivalTime;
            continue;
        }

        std::sort(readyIndices.begin(), readyIndices.end(), [&](int a, int b)
                  { return sjfProcess[a].priority < sjfProcess[b].priority; });

        int shortestJobIndex = readyIndices[0];
        CPU_Process currentProcess = sjfProcess[shortestJobIndex];
        readyIndices.erase(readyIndices.begin());

        int startTime = currentTime;
        int endTime = currentTime + currentProcess.CPU_BurstLength;

        totalWaitingTime += startTime - currentProcess.arrivalTime;
        totalTurnaroundTime += endTime - currentProcess.arrivalTime;
        totalResponseTime += startTime - currentProcess.arrivalTime;
        totalCPUBurstTime += currentProcess.CPU_BurstLength;

        currentTime = endTime;
    }

    cout << "Statistics for Preemptive Priority Scheduling\n\n";
    calculations(numOfProcesses, currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);
}