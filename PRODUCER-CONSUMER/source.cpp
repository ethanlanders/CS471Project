#include <iostream>
#include <fstream>

#include <thread>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
#include <vector>

#include "threads.h"

string runSim(int time, int producerNum, int consumerNum)
{
    string output = "";

    // Create Producer and consumer threads
    std::thread prod[producerNum];
    std::thread cons[consumerNum];
    std::thread timer;

    for (int id = 0; id < producerNum; id++)
        prod[id] = std::thread(producer);
    /* spawn consumer threads */
    for (int id = 0; id < consumerNum; id++)
        cons[id] = std::thread(consumer);

    std::cout << "\nRunning: " << time << " " << producerNum << " " << consumerNum << endl;

    /* Starts Threads */
    timer = std::thread(runThreads, time); // argv[2]);

    /* close producer threads */
    for (int id = 0; id < producerNum; id++)
        prod[id].join();
    /* close consumer threads */
    for (int id = 0; id < consumerNum; id++)
        cons[id].join();
    /* Close Timer Thread */
    timer.join();

    cout << "\n";
    return output;
}

int main(int argc, char *argv[])
{
    ifstream file;
    string line = "";

    string files[] = {"input-2sec-wait.txt",
                      "input-4sec-wait.txt",
                      "input-6sec-wait.txt"};
    for (string i : files)
    {
        file.open(i);

        // if statement to determine if input file successfully opened
        if (!file)
        {
            cerr << "Error opening " << i << endl;
            return 1;
        }

        int time, producers, consumers;
        while (file >> time >> producers >> consumers)
        {
            fstream outputFile;
            string out = "output-" + to_string(time) + "sec-wait.txt";
            outputFile.open(out);
            outputFile << runSim(time, producers, consumers);
            outputFile.close();
        }

        file.close();
    }
    // runSim(5, 5, 5);

    return 0;
}