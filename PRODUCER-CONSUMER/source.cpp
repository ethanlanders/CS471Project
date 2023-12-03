#include <iostream>
#include <fstream>

#include "threads.h"

int main(int argc, char *argv[])
{
    ifstream file;
    string line = "";
    // Open provided files containing various wait times, producers, and consumers
    string inputFiles[] = {"input-2sec-wait.txt",
                           "input-4sec-wait.txt",
                           "input-6sec-wait.txt"};
    for (string i : inputFiles)
    {
        file.open(i);

        // Validate file opened
        if (!file)
        {
            cerr << "Error opening " << i << endl;
            return 1;
        }

        // Create output file
        ofstream outputFile;
        string out = "output" + i.substr(i.find('-'));
        outputFile.open(out);

        int time, producers, consumers;
        while (file >> time >> producers >> consumers)
        {
            // Write to file
            outputFile << runSim(time, producers, consumers);
        }

        // Close both input and output files
        outputFile.close();
        file.close();
    }

    return 0;
}