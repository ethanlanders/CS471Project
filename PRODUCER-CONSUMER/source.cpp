
#include <iostream>
#include <fstream>

#include <thread>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
#include <vector>

// #include <random>
// let me save please
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

using namespace std;
bool ready = false; // Tell threads to run
std::mutex buf;     // mutex for critical section
condition_variable cv;

// Per textbook problem statement
// #include "buffer.h"

typedef int buffer_item;
vector<buffer_item> buffer;

#define BUFFER_SIZE 5

// buffer_item buffer[BUFFER_SIZE];

// buffer Functions
bool insert_item(buffer_item item)
{
    bool insert = false;
    unique_lock<mutex> lock(buf);
    cv.wait(lock);
    // Insert Item
    cv.notify_one();
    return insert; // If successful
    // return true;  // Indicating error
}

bool remove_item(buffer_item item)
{
    cout << "~Removing Start\n";
    bool remove = false;
    unique_lock<mutex> lock(buf);
    cout << "~Removing Lock\n";
    cv.wait(lock);
    cout << "~Removing Past Wait\n";
    // Remove Item
    cv.notify_one();

    cout << "~Removing End\n";
    return remove; // Nothing to remove
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
        /* sleep for a random period of time from 0-5 seconds */
        sleep(rand() % 5);
        /* generate a random number */
        cout << "Producing\n";
        item = rand();
        if (insert_item(item)) // insert_item(item))
            cout << "Producer Error: Full buffer\n";
        else
            cout << "Producer produced\n"
                 << item;
    }
}

void consumer()
{
    // buffer_item item;
    int item = 0;
    sleep(1);

    while (ready)
    {
        /* sleep for a random period of time from 0-5 seconds */
        sleep(rand() % 5);
        cout << "Consuming\n";
        if (remove_item(item)) // remove_item(&item))
            cout << "Report Error: Empty Buffer\n";
        else
            cout << "Consumer consumed\n"
                 << item;
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

    unique_lock<mutex> lock(buf);

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

    cv.notify_one();

    /* close producer threads */
    for (int id = 0; id < producerNum; id++)
        prod[id].join();
    /* close consumer threads */
    for (int id = 0; id < producerNum; id++)
        cons[id].join();
    timer.join();

    cout << "\n";
    return 0;
}