
#include <iostream>
#include <fstream>

#include <thread>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
// #include <random>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

using namespace std;
bool ready = false; // Tell threads to run
std::mutex buf;     // mutex for critical section
condition_variable cv;

// Per textbook problem statement
// #include "buffer.h"
typedef int buffer_item;
#define BUFFER_SIZE 5

buffer_item buffer[BUFFER_SIZE];

// buffer Functions
bool insert_item(buffer_item item)
{
    unique_lock<mutex> lock(buf);
    cv.wait(lock);
    // Insert Item
    cv.notify_one();
    return false; // If successful
    // return true;  // Indicating error
}

bool remove_item(buffer_item *item)
{
    unique_lock<mutex> lock(buf);
    cv.wait(lock);
    // Remove Item
    cv.notify_one();
    return false; // If successful
    // return true;  // Indicating error
}

// Threads Functions
void producer()
{
    // buffer_item item;
    int item = 0;
    sleep(1);

    while (ready)
    {
        sleep(0);
        cout << "Producing";
        /* sleep for a random period of time from 0-5 seconds */
        // sleep(rand() % 1);
        /* generate a random number */
        item = rand();
        if (true) // insert_item(item))
            cout << "report error condition";
        else
            cout << "producer produced " << item;
    }
}

void consumer()
{
    // buffer_item item;
    int item = 0;
    sleep(1);
    while (ready)
    {
        sleep(0);
        cout << "Consuming";
        /* sleep for a random period of time from 0-5 seconds */
        // sleep(rand() % 1);
        if (true) // remove_item(&item))
            cout << "report error condition";
        else
            cout << "consumer consumed " << item;
    }
}

/* Changes ready to true, and begins the threads printing */
void runThreads(int time)
{
    ready = true;
    sleep(time);
    ready = false;
}

int main(int argc, char *argv[])
{
    // Get CLI input
    int time = 5;
    int producerNum = 1;
    int consumerNum = 1;

    // Initialize Buffer

    // Create Producer and consumer threads
    std::thread prod[producerNum];
    std::thread cons[consumerNum];
    std::thread timer;

    /* spawn producer threads */
    timer = std::thread(runThreads, time);

    for (int id = 0; id < producerNum; id++)
        prod[id] = std::thread(producer);
    cout << "Created Producer Threads\n";
    /* spawn consumer threads */
    for (int id = 0; id < producerNum; id++)
        cons[id] = std::thread(consumer);
    cout << "Created Consumer Threads\n";

    std::cout << "\nRunning " << producerNum + consumerNum;
    std::cout << " in parallel: \n"
              << std::endl;

    /* close producer threads */
    cout << "Close Threads";
    for (int id = 0; id < producerNum; id++)
        prod[id].join();
    /* close consumer threads */
    for (int id = 0; id < producerNum; id++)
        cons[id].join();
    timer.join();

    cout << "\n";
    return 0;
}