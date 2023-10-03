#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CPUprocess{
    int arrivalTime;
    int CPU_BurstLength;
    int priority;
};

int main(){
    readData();
    return 0;
}

void readData(){
    //string inFileName = "datafile.txt"
    ifstream inFile;
    inFile.open("datafile.txt");

    if(inFile.is_open()){
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