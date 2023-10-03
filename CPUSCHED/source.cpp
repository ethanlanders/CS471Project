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
    inFile.open("datafile.txt");

    CPU_Process process[numOfProcesses];
    
    if(inFile.is_open()){
        // for(i=0; i<)     LOOP THROUGH FILE
        inFile.close();
    }
    else{
        cerr << "Cannot find that input file." << endl;
    }
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
