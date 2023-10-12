
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
    buffer_item item;
    while (!ready)
    {
    };
    while (true)
    {
        cout << "Producing";
        /* sleep for a random period of time from 0-5 seconds */
        sleep(rand() % 5);
        /* generate a random number */
        item = rand();
        if (insert_item(item))
            cout << "report error condition";
        else
            cout << "producer produced " << item;
    }
}

void consumer()
{
    buffer_item item;
    while (!ready)
    {
    };
    while (true)
    {
        cout << "Consuming";
        /* sleep for a random period of time from 0-5 seconds */
        sleep(rand() % 5);
        if (remove_item(&item))
            cout << "report error condition";
        else
            cout << "consumer consumed " << item;
    }
}

/* Changes ready to true, and begins the threads printing */
void runThreads()
{
    cout << "At Run";
    unique_lock<mutex> lock(buf);
    ready = true;
    cv.notify_one();

    cout << "After Run";
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

    /* spawn producer threads */

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
    cout << "Wake up Threads maybe\n";
    runThreads(); // Allows threads to run

    cout << "Sleeping";
    // Sleep then exit
    sleep(time);
    cout << "Awake";
    /* spawn producer threads */
    for (int id = 0; id < producerNum; id++)
        prod[id].join();
    /* spawn consumer threads */
    for (int id = 0; id < producerNum; id++)
        cons[id].join();

    cout << "\n";
    return 0;
}