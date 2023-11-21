#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>
#include <iostream>

using namespace std;

struct CPU_Process
{
    int arrivalTime;
    int CPU_BurstLength;
    int priority;
    int responseTime = 0;
};

inline bool compareArrivalTime(const CPU_Process &p1, const CPU_Process &p2)
{
    return p1.arrivalTime < p2.arrivalTime;
}

// Function to calculate and display statistics for CPU processes
inline void calculations(int numOfProcesses, int totalElapsedTime, int totalCPUBurstTime, int totalWaitingTime,
                  int totalResponseTime, int totalTurnaroundTime)
{

    // Calculate throughoutput (proccesses per unit of time) and CPU utilization
    double throughput = static_cast<double>(numOfProcesses) / totalCPUBurstTime;
    double cpuUtilization = static_cast<double>(totalCPUBurstTime) / totalElapsedTime;

    // Display calculations
    cout << "Number of processes: " << numOfProcesses << endl;
    cout << "Total elapsed time (for the scheduler): " << totalElapsedTime << endl;
    cout << "Throughput (Number of processes executed in one unit "
            "of CPU burst time): "
         << throughput << endl;
    cout << "CPU utilization: " << cpuUtilization << endl;
    cout << "Average waiting time (in CPU burst times): " << static_cast<double>(totalWaitingTime) / numOfProcesses << endl;
    cout << "Average turnaround time (in CPU burst times): " << static_cast<double>(totalTurnaroundTime) / numOfProcesses << endl;
    cout << "Average response time (in CPU burst times): " << static_cast<double>(totalResponseTime) / numOfProcesses << endl
         << endl
         << endl;
}

#endif