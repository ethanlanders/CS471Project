#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <bits/stdc++.h> 

#define numOfProcesses 500

using namespace std;

// Define a structure to represent a CPU process
struct CPU_Process{
    int arrivalTime;
    int CPU_BurstLength;
    int priority;
    int responseTime;
};

// Function to read CPU process data from a file named "datafile.txt"
void readData(vector<CPU_Process>& processes){
    ifstream inFile;
    string firstLine;
    inFile.open("datafile.txt");

    // if statement to determine if input file successfully opened
    if (!inFile) {
        cerr << "Error opening datafile.txt" << endl;
        return;
    } 

    int arrivalTime, CPU_BurstLength, priority;
    int processCounter = 0;

    // Read CPU process data from the input file
    getline(inFile, firstLine);
    while(inFile >> arrivalTime >> CPU_BurstLength >> priority){
        // Create a CPU_Process struct to push read in material to the processes vector
        CPU_Process p = {arrivalTime, CPU_BurstLength, priority};
        processes.push_back(p);
        processCounter++;
    }

    // Close the input file after reading in
    inFile.close();
    
    // **Test to see if input was successful**
    // for (CPU_Process p : processes) {
    //     cout << p.arrivalTime << "   " << p.CPU_BurstLength << "   " << p.priority << endl;
    // }
}

// Function to calculate and display statistics for CPU processes
void calculations(vector<CPU_Process>& processes){
    // Declare variables
    int totalElapsedTime        = 0;
    int numOfCompletedProcesses = 0;
    int totalCPUBurstTime       = 0;
    int totalWaitingTime        = 0;
    int totalTurnaroundTime     = 0;
    int totalResponseTime       = 0;
    int currentTime             = 0;
    int totalIdleTime           = 0;

    vector<CPU_Process> buffer;

    // Arrival time CPU Burst length Priority
    // 10 22 1 
    // 68 12 6
    // 98 34 8
    // 148 28 10
    // 192 3 3
    // 223 8 3
    // 266 18 2
    // 268 14 10
    // 268 30 4

    for(CPU_Process p : processes){
        // Buffer is Empty
        if(buffer.empty())
        {
            totalIdleTime = totalIdleTime + p.arrivalTime - currentTime;
            currentTime = currentTime + (p.arrivalTime - currentTime);
            buffer.push_back(p);
        } 
        // There are ___ processes in the vector
        else 
        { 
            // Calculating Time Difference
            int diff = p.arrivalTime - currentTime;

            // Updating buffer based off time difference
            for(CPU_Process b : buffer){
                if(b.CPU_BurstLength >= diff){
                    b.CPU_BurstLength -= diff;
                    diff = 0;
                    break;
                } else {
                    diff -= b.CPU_BurstLength;
                    b.CPU_BurstLength = 0;
                    if(b.CPU_BurstLength == 0){
                        buffer.erase(b.begin());
                        numOfCompletedProcesses++;
                        // if(numOfCompletedProcesses == numOfProcesses){
                        //     break;
                    }
                } 
            }

            // Updating totalIdleTime
            if(diff > 0){
                totalIdleTime += diff;
            }

            currentTime = p.arrivalTime;

            buffer.push_back(p);

            // ***sort buffer by burst for SJF.***
            // sort(buffer.CPU_BurstLength)

            // EVERYTHING BENEATH IN COMMENTS CAN BE REMOVED (most likely)

            // // remove process in buffer if finished

            // // Vector will finish before the next process
            // if((buffer.front().arrivalTime + buffer.front().CPU_BurstLength) <= p.arrivalTime){
            //     currentTime = currentTime + p.CPU_BurstLength;
            //     buffer.erase(buffer.begin());
            //     numOfCompletedProcesses++;
            // } else {
            //     if(){

            //     }
            // }
        }


        
        // // Wait for the next proccess if the current one has not arrived
        // if(p.arrivalTime > currentTime) {
        //     currentTime = p.arrivalTime;
        // }

        // // Calculate response time
        // int responseTime = currentTime - p.arrivalTime;
        // totalResponseTime += responseTime;

        // // Calculate waiting time
        // int waitingTime = currentTime - p.arrivalTime;
        // totalWaitingTime += waitingTime;

        // // Simulate the CPU's burst time
        // currentTime += p.CPU_BurstLength;

        // // Calculate turnaround time
        // int turnaroundTime = currentTime - p.arrivalTime;
        // totalTurnaroundTime += turnaroundTime;

        // // Calculate total CPU burst time
        // totalCPUBurstTime += p.CPU_BurstLength;

        // // Increment the number of completed processes
        // numOfCompletedProcesses++;

        // // Exit the loop when 500 processes are completed
        // if(numOfCompletedProcesses >= 500){
        //     break;
        // }
    }

    // Set total elapsed time to what the current time is at the end of calculations
    totalElapsedTime = currentTime;

    // Calculate throughoutput (proccesses per unit of time) and CPU utilization
    double throughput = static_cast<double>(numOfCompletedProcesses) / totalElapsedTime;
    double cpuUtilization = static_cast<double>(totalCPUBurstTime) / totalElapsedTime;

    // Display calculations 
    cout << "Number of processes: " << numOfProcesses << endl;
    cout << "Total elapsed time (for the scheduler): " << totalElapsedTime << endl;
    cout << "Throughput (Number of processes executed in one unit " 
            "of CPU burst time): " << throughput << endl;
    cout << "CPU utilization: " << cpuUtilization << endl;
    cout << "Average waiting time (in CPU burst times): " << static_cast<double>(totalWaitingTime)/numOfCompletedProcesses << endl;
    cout << "Average turnaround time (in CPU burst times): " << static_cast<double>(totalTurnaroundTime)/numOfCompletedProcesses << endl;
    cout << "Average response time (in CPU burst times): " << static_cast<double>(totalResponseTime)/numOfCompletedProcesses << endl << endl << endl;
} 

// Function to perform First-In-First-Out (FIFO) Scheduling
void FIFO(vector<CPU_Process> processes){
    cout << "\nStatistics for FIFO Scheduling\n\n";
    calculations(processes);
}

// Function to perform Shortest-Job First (SJF) Scheduling
void SJF(vector<CPU_Process> processes){
    // Sort vector from shortest to longest CPU burst length for each process
    sort(processes.begin(), processes.end(), [](CPU_Process a, CPU_Process b) 
         {return a.CPU_BurstLength < b.CPU_BurstLength;});

    // Test if sorting worked properly
    // for (CPU_Process p : processes) {
    //     cout << p.arrivalTime << "   " << p.CPU_BurstLength << "   " << p.priority << endl;
    // }

    cout << "\nStatistics for SJF Scheduling\n\n";
    calculations(processes);
}


// Function to perform Preemptive Priority Scheduling
void preemptivePriority(vector<CPU_Process>& processes){
    
    cout << "\nStatistics for Preemptive Priority Scheduling\n\n";
    calculations(processes);
}

int main(){
    // Declare needed variables
    vector<CPU_Process> processes;

    // Read process data from the input file, save to vector of processes
    readData(processes);

    // Perform FIFO CPU scheduling 
    FIFO(processes);
 
    // Perform SJF CPU scheduling
    SJF(processes);

    // Perform Preemptive Priority Scheduling
    preemptivePriority(processes);

    return 0;
}

