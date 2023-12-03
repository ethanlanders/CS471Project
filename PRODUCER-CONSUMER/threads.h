#ifndef THREADS_H
#define THREADS_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <unistd.h>

#include <iostream>
using namespace std;
bool ready = true; // Tell threads to run
bool quit = false; // End threads
std::mutex buf;    // mutex for critical section
condition_variable cv;

// Per textbook problem statement
// #include "buffer.h"
vector<int> buffer;

#define BUFFER_SIZE 5

// buffer Functions
bool insert_item(int item)
{
    bool insert = false;
    unique_lock<mutex> lock(buf);

    if (buffer.size() < BUFFER_SIZE)
    {
        buffer.push_back(item);
        if (buffer.back() == item)
            insert = true;
    }

    cv.notify_all();
    return insert;
}

bool remove_item(int &item)
{
    bool remove = false;
    unique_lock<mutex> lock(buf);

    if (buffer.size() > 0)
    {
        item = buffer.front();
        buffer.erase(buffer.begin());
        remove = true;
    }

    cv.notify_all();
    return remove;
}

// Threads Functions
void producer(string &output)
{
    // buffer_item item;
    int item = 0;

    while (!quit)
    {
        while (ready)
        {
        }
        /* sleep for a random period of time from 0-5 seconds */
        sleep(rand() % 5);
        /* generate a random number */
        item = rand() % 100;
        if (!insert_item(item)) // insert_item(item))
            output += "Producer Error: Full buffer\n";
        else
            output += "Producer produced " + to_string(item) + "\n";
    }
}

void consumer(string &output)
{
    // buffer_item item;
    int item = 0;

    while (!quit)
    {
        while (ready)
        {
        }
        /* sleep for a random period of time from 0-5 seconds */
        sleep(rand() % 5);
        if (!remove_item(item)) // remove_item(&item))
            output += "Consumer Error: Empty Buffer\n";
        else
            output += "Consumer consumed " + to_string(item) + "\n";
    }
}

/* Changes ready to true, and begins the threads printing */
void runThreads(int time)
{
    ready = false;
    sleep(time);
    quit = true;
}

string runSim(int time, int producerNum, int consumerNum)
{
    buffer.clear();
    string output = "";

    // Create Producer and consumer threads
    std::thread prod[producerNum];
    std::thread cons[consumerNum];
    std::thread timer;

    for (int id = 0; id < producerNum; id++)
        prod[id] = std::thread(producer, ref(output));
    /* spawn consumer threads */
    for (int id = 0; id < consumerNum; id++)
        cons[id] = std::thread(consumer, ref(output));

    output += "\nRunning: " + to_string(time) + " " + to_string(producerNum) + " " + to_string(consumerNum) + "\n";

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

    ready = true; // Tell threads to run
    quit = false; // End threads

    return output;
}

#endif