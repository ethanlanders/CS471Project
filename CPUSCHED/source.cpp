#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <bits/stdc++.h>
// Do not use hardcoded process count value
#define numOfProcesses 541

using namespace std;

// Define a structure to represent a CPU process
struct CPU_Process
{
    int arrivalTime;
    int CPU_BurstLength;
    int priority;
    int responseTime;
};

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

    //cout<<"processCounter:" <<processCounter <<endl;

    // **Test to see if input was successful**
    // for (CPU_Process p : processes) {
    //     cout << p.arrivalTime << "   " << p.CPU_BurstLength << "   " << p.priority << endl;
    // }
}

// Function to calculate and display statistics for CPU processes
void calculations(int totalElapsedTime, int totalCPUBurstTime, int totalWaitingTime,
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


bool compareArrivalTime(const CPU_Process& p1, const CPU_Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

// Function to perform First-In-First-Out (FIFO) Scheduling
void FIFO(vector<CPU_Process> processes)
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

    while (currentIndex < numOfProcesses || !readyIndices.empty()) {
        while (currentIndex < numOfProcesses && sjfProcess[currentIndex].arrivalTime <= currentTime) {
            readyIndices.push_back(currentIndex);
            currentIndex++;
        }

        if (readyIndices.empty()) {
            currentTime = sjfProcess[currentIndex].arrivalTime;
            continue;
        }

        std::sort(readyIndices.begin(), readyIndices.end(), [&](int a, int b) {
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
        totalCPUBurstTime += currentProcess.CPU_BurstLength;

        currentTime = endTime;
    }


    cout << "\nStatistics for SJF Scheduling\n\n";
    calculations(currentTime, totalCPUBurstTime, totalWaitingTime, totalResponseTime, totalTurnaroundTime);


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
