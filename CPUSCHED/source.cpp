#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Define a structure to represent a CPU process

// #include "helper_Functions.h"
#include "FIFO.h"

// Function to read CPU process data from a file named "datafile.txt"
void readData(vector<CPU_Process> &processes)
{

    ifstream inFile;
    string firstLine;
    inFile.open("datafile.txt");

    // if statement to determine if input file successfully opened
    if (!inFile)
    {
        cerr << "Error opening datafile.txt" << endl;
        return;
    }

    int arrivalTime, CPU_BurstLength, priority;
    int processCounter = 0;

    // Read CPU process data from the input file
    getline(inFile, firstLine);
    while (inFile >> arrivalTime >> CPU_BurstLength >> priority)
    {
        // Create a CPU_Process struct to push read in material to the processes vector
        CPU_Process p = {arrivalTime, CPU_BurstLength, priority};
        processes.push_back(p);
        processCounter++; // use this variable to access process count I cout this variable It is giving record 541 in line 51
    }

    // Close the input file after reading in
    inFile.close();

    // cout<<"processCounter:" <<processCounter <<endl;

    // **Test to see if input was successful**
    // for (CPU_Process p : processes) {
    //     cout << p.arrivalTime << "   " << p.CPU_BurstLength << "   " << p.priority << endl;
    // }
}

// Function to perform Shortest-Job First (SJF) Scheduling
void SJF(vector<CPU_Process> processes)
{
    std::vector<CPU_Process> sjfProcess = processes;
    std::sort(sjfProcess.begin(), sjfProcess.end(), compareArrivalTime);

    // Declare variables
    int totalElapsedTime = 0;
    int numOfCompletedProcesses = 0;
    int totalCPUBurstTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    //    int currentTime = 0;
    int totalIdleTime = 0;

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

    cout << "\nStatistics for SJF Scheduling\n\n";
    calculations(numOfCompletedProcesses, currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);

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

// Function to perform Preemptive Priority Scheduling
void preemptivePriority(vector<CPU_Process> &processes)
{

    cout << "\nStatistics for Preemptive Priority Scheduling\n\n";
    // calculations(totalElapsedTime, totalCPUBurstTime, totalIdleTime,
    //              totalWaitingTime, totalResponseTime, totalTurnaroundTime);
}

int main()
{
    // Declare needed variables
    vector<CPU_Process> processes;

    // Read process data from the input file, save to vector of processes
    readData(processes);

    // Perform FIFO CPU scheduling
    //    FIFO(processes);

    // Perform SJF CPU scheduling
    SJF(processes);

    // Perform Preemptive Priority Scheduling
    //    preemptivePriority(processes);

    return 0;
}
