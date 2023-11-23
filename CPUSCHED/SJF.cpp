#include "SJF.h"

// Function to perform Shortest-Job First (SJF) Scheduling
void SJF(vector<CPU_Process> processes)
{
    std::vector<CPU_Process> sjfProcess = processes;
    std::sort(sjfProcess.begin(), sjfProcess.end(), compareArrivalTime);

    // Declare variables 
    int numOfProcesses = 541;
    int totalCPUBurstTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
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
                  { return sjfProcess[a].CPU_BurstLength < sjfProcess[b].CPU_BurstLength; });

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