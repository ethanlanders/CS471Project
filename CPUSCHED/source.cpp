#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#include "FIFO.h"
#include "SJF.h"
#include "preemptive.h"

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

    // cout<<"processCounter:" <<processCounter <<endl;

    // **Test to see if input was successful**
    // for (CPU_Process p : processes) {
    //     cout << p.arrivalTime << "   " << p.CPU_BurstLength << "   " << p.priority << endl;
    // }
}

int main()
{
    // Declare needed variables
    vector<CPU_Process> processes;

    // Read process data from the input file, save to vector of processes
    readData(processes);

    // Perform FIFO CPU scheduling and write output to FIFO.txt
    std::ofstream fifoFile("Output-FIFOScheduling.txt");
    std::cout.rdbuf(fifoFile.rdbuf());  // Redirect cout to the file
    FIFO(processes);
    fifoFile.close(); // Close the file

    // Perform SJF CPU scheduling and write output to SJF.txt
    std::ofstream sjfFile("Output-SJFScheduling.txt");
    std::cout.rdbuf(sjfFile.rdbuf());  // Redirect cout to the file
    SJF(processes);
    sjfFile.close(); // Close the file

    // Perform preemptive priority CPU scheduling and write output to preemptive.txt
    std::ofstream preemptiveFile("Output-PriorityScheduling.txt");
    std::cout.rdbuf(preemptiveFile.rdbuf());  // Redirect cout to the file
    preemptivePriority(processes);
    preemptiveFile.close(); // Close the file

    return 0;
}
