#include "SJF.h"

using namespace std;

// Function to perform Shortest-Job First (SJF) Scheduling
void SJF(vector<CPU_Process> processes)
{
    std::cout << "\n~~Reached SJ\n";

    // Hold a copy of the processes
    std::vector<CPU_Process> sjfProcess = processes;

    std::sort(sjfProcess.begin(), sjfProcess.end(), compareArrivalTime);

    /*  Declare variables   */

    // Number of processes we are working with contained within datafile.txt
    int numOfProcesses = 0;

    // Total amount of time CPU is working on a process
    int totalCPUBurstTime = 0;

    // The extra time it takes for the CPU to complete a process
    int totalWaitingTime = 0;

    // Time between when a process arrives and when it completes
    int totalTurnaroundTime = 0;

    // Time it takes for the CPU to intially start working on a process
    int totalResponseTime = 0;

    int currentTime = 0; // sjfProcess[0].arrivalTime;

    // Vector that holds the integer index to the processes that need to be completed
    std::vector<int> readyIndices;

    int currentIndex = 0; // Keep track of the current process index

    int idleTime = 0;

    // While we have not scheduled every process in datafile or the buffer contains processes... work on processes
    while (currentIndex < processes.size() || !readyIndices.empty())
    {
        // The buffer is empty when no processes are ready to execute.
        // If that is the case, then update currentTime with the next
        // processes's arrival time.  The loop continues afterwards.
        if (readyIndices.empty())
        {
            idleTime += sjfProcess[currentIndex].arrivalTime - currentTime;
            currentTime = sjfProcess[currentIndex].arrivalTime;
        }

        // While we have not scheduled everything
        // and the current index's process's arrival time is less than the current time...
        // add processes to the buffer
        // so... if there are two processes with the same arrival time, save one to the buffer.
        // currentTime == 98
        // Sjf current index == 1
        // sjfProcess[currentIndex].arrivalTime == 68
        // now... readyIndices contains '1'
        // currentIndex == 2 now...
        // 98 == 98 now
        // add index '2' to readyIndices
        // currentIndex == 3 now...
        // continue doing this until
        while (currentIndex < processes.size() && sjfProcess[currentIndex].arrivalTime <= currentTime)
        {
            readyIndices.push_back(currentIndex);
            currentIndex++;
        }

        // 268 14 10
        // 266 18 2
        // *268 30 4    currentTime = 268
        // 296 10 7

        // Sort the buffer based on CPU burst length of processes in SJF scheduling
        std::sort(readyIndices.begin(), readyIndices.end(), [&](int a, int b)
                  { 
                    // if (sjfProcess[a].CPU_BurstLength == sjfProcess[b].CPU_BurstLength) {
                    //     // If CPU burst lengths are equal, prioritize by arrival order
                    //     return sjfProcess[a].arrivalTime < sjfProcess[b].arrivalTime;
                    // }
                    return sjfProcess[a].CPU_BurstLength < sjfProcess[b].CPU_BurstLength; });

        int timeTillNextProcess = sjfProcess[currentIndex].arrivalTime - currentTime;

        for (int i : readyIndices)
        {
            if (currentIndex == processes.size() || timeTillNextProcess > 0) // While there is time to work on a process
            {
                // Check to see if we have worked on the process at all
                if (!sjfProcess[i].responseTime)
                {
                    totalResponseTime += currentTime - sjfProcess[i].arrivalTime;
                    sjfProcess[i].responseTime = true;
                }
                // Not enough time to finish process
                if (currentIndex < processes.size() && sjfProcess[i].CPU_BurstLength > timeTillNextProcess)
                {
                    sjfProcess[i].CPU_BurstLength -= timeTillNextProcess;
                    currentTime += timeTillNextProcess;
                    break;
                }
                else
                { // Can finish process
                    timeTillNextProcess -= sjfProcess[i].CPU_BurstLength;
                    currentTime += sjfProcess[i].CPU_BurstLength;
                    numOfProcesses++;

                    totalWaitingTime += currentTime - (processes[i].arrivalTime + processes[i].CPU_BurstLength);
                    totalTurnaroundTime += currentTime - processes[i].arrivalTime;

                    sjfProcess[i].CPU_BurstLength = 0;
                    readyIndices.erase(readyIndices.begin());
                }
            }
            else
            {
                break;
            }
        }
    }
    totalCPUBurstTime = currentTime - idleTime;
    std::cout << "Statistics for SJF Scheduling\n\n";
    calculations(numOfProcesses, currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);
}