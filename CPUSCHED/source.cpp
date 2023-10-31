#include <iostream>
#include <fstream>
#include <string>
#include <queue>

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
    int totalElapsedTime        = 0;
    int numOfCompletedProcesses = 0;
    int totalCPUBurstTime       = 0;
    int totalWaitingTime        = 0;
    int totalTurnaroundTime     = 0;
    int totalResponseTime       = 0;
    int currentTime             = 0;

    for(CPU_Process p : processes){
        if(p.arrivalTime > currentTime) {
            currentTime = p.arrivalTime;
        }

        int responseTime = currentTime - p.arrivalTime;
        totalResponseTime += responseTime;

        int waitingTime = currentTime - p.arrivalTime;
        totalWaitingTime += waitingTime;

        currentTime += p.CPU_BurstLength;

        int turnaroundTime = currentTime - p.arrivalTime;
        totalTurnaroundTime += turnaroundTime;

        totalCPUBurstTime += p.CPU_BurstLength;

        numOfCompletedProcesses++;

        if(numOfCompletedProcesses >= 500){
            break;
        }
    }

    totalElapsedTime = currentTime;

    double throughput = static_cast<double>(numOfCompletedProcesses) / totalElapsedTime;
    double cpuUtilization = static_cast<double>(totalCPUBurstTime) / totalElapsedTime;

    // Display calculations 
    cout << "\nStatistics for the Run\n\n";
    cout << "Number of processes: " << numOfProcesses << endl;
    cout << "Total elapsed time (for the scheduler): " << totalElapsedTime << endl;
    cout << "Throughput (Number of processes executed in one unit " 
            "of CPU burst time): " << throughput << endl;
    cout << "CPU utilization: " << cpuUtilization << endl;
    cout << "Average waiting time (in CPU burst times): " << static_cast<double>(totalWaitingTime)/numOfCompletedProcesses << endl;
    cout << "Average turnaround time (in CPU burst times): " << static_cast<double>(totalTurnaroundTime)/numOfCompletedProcesses << endl;
    cout << "Average response time (in CPU burst times): " << static_cast<double>(totalResponseTime)/numOfCompletedProcesses << endl << endl;
}

// Function to perform First-In-First-Out (FIFO) Scheduling
void FIFO(vector<CPU_Process>& processes){
    int time = 0;

    calculations(processes);
}

// Function to perform Shortest-Job First (SJF) Scheduling
// void SJF(){
//     output();
// }


// Function to perform Preemptive Priority Scheduling
// void preemptivePriority(){
//     output();
// }

int main(){
    // Declare needed variables
    vector<CPU_Process> processes;

    // Read process data from the input file, save to vector of processes
    readData(processes);

    // Perform FIFO CPU scheduling 
    FIFO(processes);

    return 0;
}

