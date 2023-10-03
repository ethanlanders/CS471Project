#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class CPU_Process{
    public:
        int arrivalTime;
        int CPU_BurstLength;
        int priority;

    CPU_Process(int arrivalTime, int CPU_BurstLength, int priority){
        arrivalTime = 0;
        CPU_BurstLength = 0;
        priority = 0;
    }


};

int main(){
    readData();
    return 0;
}

void readData(){
    //string inFileName = "datafile.txt"
    ifstream inFile;
    inFile.open("datafile.txt");

    CPU_Process process[];
    
    if(inFile.is_open()){
        // for(i=0; i<)     LOOP THROUGH FILE
        inFile >> process->arrivalTime >> process->CPU_BurstLength >> process->priority;
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