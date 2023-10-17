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
};

void readData(CPU_Process process[]){
    ifstream inFile;
    string firstLine;
    inFile.open("datafile.txt");

    if(inFile.is_open()){
        getline(inFile, firstLine);
        for(int i=0; i<numOfProcesses; i++){
            inFile >> process[i].arrivalTime >> process[i].CPU_BurstLength >> process[i].priority;
        }
        inFile.close();
    }
    else{
        cerr << "Cannot find that input file." << endl;
    }
    // // Testing to make sure reading in from .txt was successful.
    // for(int i=0; i<numOfProcesses; i++){
    //     cout << firstLine;
    //     cout << process[i].arrivalTime << "   " << process[i].CPU_BurstLength << "   " << process[i].priority << endl;
    // }
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

void FIFO(queue<CPU_Process>& q){
    
    int time = 0;

    while(!q.empty()){
        CPU_Process process = q.front();

    }

    output();
}

void SJF(queue<CPU_Process>& q){
    output();
}

void preemptivePriority(queue<CPU_Process>& q){
    output();
}

int main(){
    // Declare needed variables
    queue<CPU_Process> q;
    CPU_Process process[numOfProcesses];

    // Read from input file
    readData(process);
    
    for (const CPU_Process& p : process) {
        q.push(p);
    }

    FIFO(q);

    // Test
    for(int i=0; i<20; i++){
        cout << process[i].arrivalTime << " " << process[i].CPU_BurstLength << " " << process[i].priority << endl;
    }
    return 0;
}
