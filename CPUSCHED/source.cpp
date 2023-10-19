#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#define numOfProcesses 500

using namespace std;

struct CPU_Process{
    int arrivalTime;
    int CPU_BurstLength;
    int priority;
    int responseTime;
};

void readData(vector<CPU_Process>& processes){
    ifstream inFile;
    string firstLine;
    inFile.open("datafile.txt");

    int arrivalTime, CPU_BurstLength, priority;
    int processCounter = 0;
    getline(inFile, firstLine);
    while(inFile >> arrivalTime >> CPU_BurstLength >> priority){
        CPU_Process p = {arrivalTime, CPU_BurstLength, priority};
        processes.push_back(p);
        processCounter++;
    }
    inFile.close();
}

void calculations(vector<CPU_Process>& processes){
    int totalElapsedTime = 0;
    int numOfCompletedProcesses = 0;
    int totalCPUBurstTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    int currentTime = 0;

    // For 500 processes in the vector...
    for(int i=0; i<numOfProcesses; i++){
        const CPU_Process& p = processes[i];

        int responseTime = currentTime - p.arrivalTime;
        totalElapsedTime += p.CPU_BurstLength;

        int waitingTime = currentTime - p.arrivalTime;
        totalWaitingTime += waitingTime;

        currentTime += p.CPU_BurstLength;
    }
}

void output(){
    cout << "Statistics for the Run\n\n";
    cout << "Number of processes: " << numOfProcesses << endl;
    cout << "Total elapsed time (for the scheduler): " << endl;
    cout << "Throughput (Number of processes executed in one unit " 
            "of CPU burst time): " << endl;
    cout << "CPU utilization: " << endl;
    cout << "Average waiting time (in CPU burst times): " << endl;
    cout << "Average turnaround time (in CPU burst times): " << endl;
    cout << "Average response time (in CPU burst times): " << endl;
}

void FIFO(vector<CPU_Process>& processes){
    
    int time = 0;

    // while(!q.empty()){
    //     CPU_Process process = q.front();

    // }
    calculations(processes);
    output();
}

// void SJF(queue<CPU_Process>& q){
//     output();
// }

// void preemptivePriority(queue<CPU_Process>& q){
//     output();
// }

int main(){
    // Declare needed variables
    // queue<CPU_Process> q;
    vector<CPU_Process> processes;
    
    // for (const CPU_Process& p : process) {
    //     q.push(p);
    // }

    //FIFO(processes);

    // Test
    // for (const CPU_Process& p : process) {
    //     cout << p.arrivalTime << "   " << p.CPU_BurstLength << "   " << p.priority << endl;
    // }
    // return 0;

    // If code works:
    cout << "Compiled successfully!" << endl;
}
