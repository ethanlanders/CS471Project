
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
vector<int> buffer;

#define BUFFER_SIZE 5

// buffer_item buffer[BUFFER_SIZE];
  
// buffer Functions
bool insert_item(int item)
{
    bool insert = false;
    unique_lock<mutex> lock(buf);

    if(buffer.size() < BUFFER_SIZE){
        buffer.push_back(item);
        if(buffer.back() == item)
            insert = true;
    }

    cv.notify_one();
    return insert;
} 

bool remove_item(int& item)
{
    bool remove = false;
    unique_lock<mutex> lock(buf);

    if(buffer.size() > 0){
        item = buffer.front();
        buffer.erase(buffer.begin());
        remove = true;
    }
 
    cv.notify_one();
    return remove;
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
        item = rand()%100;
        if (!insert_item(item)) // insert_item(item))
            cout << "Producer Error: Full buffer\n";
        else
            cout << "Producer produced "
                 << item << "\n";
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
        if (!remove_item(item)) // remove_item(&item))
            cout << "Consumer Error: Empty Buffer\n";
        else
            cout << "Consumer consumed "
                 << item << "\n";
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
    int time = 20;
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
    for (int id = 0; id < producerNum; id++)
        prod[id].join();
    /* close consumer threads */
    for (int id = 0; id < producerNum; id++)
        cons[id].join();
    timer.join();

    cout << "\n";
    return 0;
}