#include "SJF.h"

using namespace std;

// Function to perform Shortest-Job First (SJF) Scheduling
void SJF(vector<CPU_Process> processes)
{
    // Hold a copy of the processes
    std::vector<CPU_Process> sjfProcess = processes;

    // Ensures Vector of Processes is in order of arrival
    std::sort(sjfProcess.begin(), sjfProcess.end(), compareArrivalTime);

    /*  Declare variables   */
    int numOfProcesses = 0;      // Number of Completed Processes
    int totalWaitingTime = 0;    // The extra time it takes for the CPU to complete a process
    int totalTurnaroundTime = 0; // Time between when a process arrives and when it completes
    int totalResponseTime = 0;   // Time it takes for the CPU to intially start working on a process
    int currentTime = 0;         // Starting Time;
    int idleTime = 0;            // To calculate CPUBurstTime

    // Vector that holds the integer index to the processes that need to be completed
    std::vector<int> readyIndices;
    int currentIndex = 0; // Keep track of the current process index

    // While we have not scheduled every process in datafile or the buffer contains processes... work on processes
    while (currentIndex < processes.size() || !readyIndices.empty())
    {
        // Account for Idle time when buffer is empty until next process
        if (readyIndices.empty())
        {
            idleTime += sjfProcess[currentIndex].arrivalTime - currentTime;
            currentTime = sjfProcess[currentIndex].arrivalTime;
        }

        // Add Processes to index Buffer up to CurrentTime
        while (currentIndex < processes.size() && sjfProcess[currentIndex].arrivalTime <= currentTime)
        {
            readyIndices.push_back(currentIndex);
            currentIndex++;
        }

        // Sort the buffer based on CPU burst length of processes in SJF scheduling
        std::sort(readyIndices.begin(), readyIndices.end(), [&](int a, int b)
                  { return sjfProcess[a].CPU_BurstLength < sjfProcess[b].CPU_BurstLength; });

        // CPU has time till next process arrives to work on current processes
        int timeTillNextProcess = sjfProcess[currentIndex].arrivalTime - currentTime;

        vector<int> temp = readyIndices; // Temporary list to properly remove indexes from list
        // While there are processes to work on in buffer
        for (int i = 0; i < readyIndices.size(); i++)
        {
            // While there is time to work on a process
            if (currentIndex == processes.size() || timeTillNextProcess > 0)
            {
                // Check to see if we have worked on the process at all, calculate totalResponse Time if we have not
                if (!sjfProcess[readyIndices[i]].responseTime)
                {
                    totalResponseTime += currentTime - sjfProcess[readyIndices[i]].arrivalTime;
                    sjfProcess[readyIndices[i]].responseTime = true;
                }

                // Not enough time to finish process, update CPU_BurstLength
                if (currentIndex < processes.size() && sjfProcess[readyIndices[i]].CPU_BurstLength > timeTillNextProcess)
                {
                    sjfProcess[readyIndices[i]].CPU_BurstLength -= timeTillNextProcess;
                    currentTime += timeTillNextProcess;
                    break;
                }
                else
                { // Can finish process, calculate variables
                    timeTillNextProcess -= sjfProcess[readyIndices[i]].CPU_BurstLength;
                    currentTime += sjfProcess[readyIndices[i]].CPU_BurstLength;
                    numOfProcesses++;

                    totalWaitingTime += currentTime - (processes[readyIndices[i]].arrivalTime + processes[readyIndices[i]].CPU_BurstLength);
                    totalTurnaroundTime += currentTime - processes[readyIndices[i]].arrivalTime;

                    sjfProcess[readyIndices[i]].CPU_BurstLength = 0;
                    temp[i] = 0;
                }
            }
            else // No more time to work on processes
            {
                break;
            }
        }

        // Removing completed processes and update ReadyIndicies
        while (!temp.empty() && temp.front() == 0)
        {
            temp.erase(temp.begin());
        }
        readyIndices = temp;
    }

    int totalCPUBurstTime = currentTime - idleTime;
    std::cout << "Statistics for Preemptive Priority Scheduling\n\n";
    calculations(numOfProcesses, currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);
}