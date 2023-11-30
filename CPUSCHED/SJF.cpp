#include "SJF.h"

// Function to perform Shortest-Job First (SJF) Scheduling
void SJF(vector<CPU_Process> processes)
{
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

    int currentTime = sjfProcess[0].arrivalTime;

    // Vector that holds the integer index to the processes that need to be completed
    std::vector<int> readyIndices;

    int currentIndex = 0; // Keep track of the current process index

    while (currentIndex < processes.size() || !readyIndices.empty())
    {
        // Add processes to the buffer based on arrival time
        // Asking where are we in this scheduling scheme?
        while (currentIndex < processes.size() && sjfProcess[currentIndex].arrivalTime <= currentTime)
        {
            readyIndices.push_back(currentIndex);
            currentIndex++;
        }

        // The buffer is empty when no processes are ready to execute.  
        // If that is the case, then update currentTime with the next 
        // processes's arrival time.  The loop continues afterwards.
        if (readyIndices.empty())
        {
            currentTime = sjfProcess[currentIndex].arrivalTime;
            continue;
        }

        // Sort the buffer based on CPU burst length of processes in SJF scheduling
        std::sort(readyIndices.begin(), readyIndices.end(), [&](int a, int b)
                { 
                    // if (sjfProcess[a].CPU_BurstLength == sjfProcess[b].CPU_BurstLength) {
                    //     // If CPU burst lengths are equal, prioritize by arrival order
                    //     return sjfProcess[a].arrivalTime < sjfProcess[b].arrivalTime;
                    // }
                    return sjfProcess[a].CPU_BurstLength < sjfProcess[b].CPU_BurstLength;
                });


        int shortestJobIndex = readyIndices[0];
        CPU_Process currentProcess = sjfProcess[shortestJobIndex];
        readyIndices.erase(readyIndices.begin());

        int startTime = currentTime;
        int endTime = currentTime + currentProcess.CPU_BurstLength;

        totalWaitingTime += startTime - currentProcess.arrivalTime;
        totalTurnaroundTime += endTime - currentProcess.arrivalTime;
        totalResponseTime += startTime - currentProcess.arrivalTime;
        totalCPUBurstTime += currentProcess.CPU_BurstLength; // add idle time

        numOfProcesses++;

        currentTime = endTime;
    }

    cout << "Statistics for SJF Scheduling\n\n";
    calculations(numOfProcesses, currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);

    //    vector<CPU_Process> buffer;
    //
    //    cout << processes.size() << endl;
    //
    //    int num = 0;
    //    for (CPU_Process p : processes)
    //    {
    //        num++;
    //
    //        cout << "P: " << num << " B: " << numOfCompletedProcesses << endl;
    //        // Buffer is Empty
    //        if (buffer.empty())
    //        {
    //            totalIdleTime = totalIdleTime + p.arrivalTime - currentTime;
    //            currentTime = currentTime + (p.arrivalTime - currentTime);
    //            buffer.push_back(p);
    //        }
    //        else
    //        {
    //            // Calculating Time Difference
    //            int diff = p.arrivalTime - currentTime;
    //
    //            // Updating buffer based off time difference
    //            for (CPU_Process b : buffer)
    //            {
    //                cout << "\tBuffer Size: " << buffer.size() << endl;
    //                // cout << "entered for loop looping on processes in buffer" << endl;
    //                if (b.CPU_BurstLength >= diff)
    //                {
    //                    b.CPU_BurstLength -= diff;
    //                    diff = 0;
    //                    cout << "\tBuffer Item " << b.CPU_BurstLength << "" << endl;
    //                    break;
    //                }
    //                else
    //                {
    //                    cout << "\tCompleted Process" << endl;
    //                    diff -= b.CPU_BurstLength;
    //                    b.CPU_BurstLength = 0;
    //                    if (b.CPU_BurstLength == 0)
    //                    {
    //                        // cout << "Buffer process burst length == 0" << endl;
    //                        buffer.erase(buffer.begin());
    //                        numOfCompletedProcesses++;
    //                        if (numOfCompletedProcesses >= numOfProcesses)
    //                        {
    //
    //                            cout << "\tP: " << num << " B: " << numOfCompletedProcesses << endl;
    //                            cout << "\nStatistics for SJF Scheduling\n\n";
    //                            calculations(totalElapsedTime, totalCPUBurstTime,
    //                                         totalWaitingTime, totalResponseTime, totalTurnaroundTime);
    //                            return;
    //                        }
    //                    }
    //                }
    //            }
    //
    //            // Updating totalIdleTime
    //            if (diff > 0)
    //            {
    //                totalIdleTime += diff;
    //            }
    //
    //            currentTime = p.arrivalTime;
    //
    //            buffer.push_back(p); // why you are adding in the buffer at the end?
    //
    //
    //
    //
    //            // ***sort buffer by burst for SJF.***
    //            // sort(buffer.CPU_BurstLength);
    //        }
    //    }
}