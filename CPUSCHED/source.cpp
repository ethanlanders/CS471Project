#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define numOfProcesses 500

using namespace std;

struct CPU_Process{
    int arrivalTime;
    int CPU_BurstLength;
    int priority;  
};

void readData(){
    //string inFileName = "datafile.txt"
    ifstream inFile;
    string firstLine;
    inFile.open("datafile.txt");

    CPU_Process process[numOfProcesses];
    
    if(inFile.is_open()){
        getline(inFile, firstLine);
        cout << firstLine;
        for(int i=0; i<numOfProcesses; i++){
            inFile >> process[i].arrivalTime >> process[i].CPU_BurstLength >> process[i].priority;
        }
        inFile.close();
    }
    else{
        cerr << "Cannot find that input file." << endl;
    }
    // // Testing output
    // for(int i=0; i<numOfProcesses; i++){
    //     cout << process[i].arrivalTime << "   " << process[i].CPU_BurstLength << "   " << process[i].priority << endl;
    // }
}

void FIFO(){


}

void SJF(){


}

void preemptivePriority(){
    
}

int main(){
    readData();
    return 0;
}
