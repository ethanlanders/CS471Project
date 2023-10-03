
#include <iostream>
#include <fstream>

#include <thread>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
// #include <random>

using namespace std;
std::mutex account; // mutex for critical section
condition_variable cv;
bool ready = false;   // Tell threads to run
int loop[2] = {0, 0}; // current count
int balance = 0;

int update_balance(int amount)
{
    balance = balance + amount;
    int updated = balance;
    return updated;
}

int find_balance(int id)
{
    unique_lock<mutex> lock(account);
    cv.wait(lock);
    int updated = update_balance(0);
    cout << "\nThread " << id << " Balance: $" << updated;
    cv.notify_one();
    return updated;
}

/* Changes ready to true, and begins the threads printing */
void run()
{
    unique_lock<mutex> lock(account);
    ready = true;
    cv.notify_one();
}

/* Prints the thread id / max number of threads */
void print_num(int id)
{
    while (loop[0] < 2 || loop[1] < 2)
    {
        if (loop[id] < 2)
        {
            find_balance(id);
            loop[id]++;
        }
    }
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Per textbook problem statement
typedef int buffer_item;
#define BUFFER_SIZE 5

buffer_item buffer[BUFFER_SIZE];

// buffer Functions
int insert_item(buffer_item item)
{
    return 0;
}

int remove_item(buffer_item *item)
{
    return 0;
}

// Threads Functions
#include "buffer.h"
void *producer()
{
    buffer item item;
    while (true)
    {
        /* sleep for a random period of time */
        sleep(...);
        /* generate a random number */
        item = rand();
        if (insert_item(item))
            fprintf("report error condition");
        else
            printf("producer produced %d\n", item);
    }
}

void *consumer()
{
    buffer item item;
    while (true)
    {
        /* sleep for a random period of time */
        sleep(...);
        if (remove_item(&item))
            fprintf("report error condition");
        else
            printf("consumer consumed %d\n", item);
    }
}

int main(int argc, char *argv[])
{
    // Get CLI input
    int time = 5;
    int producerNum = 1;
    int consumerNum = 1;

    // Initialize Buffer

    // Create Producer and consumer threads
    std::thread producer[producerNum];
    std::thread consumer[consumerNum];

    /* spawn producer threads */
    for (int id = 0; id < producerNum; id++)
        producer[id] = std::thread(producer());
    /* spawn consumer threads */
    for (int id = 0; id < producerNum; id++)
        consumer[id] = std::thread(consumer());

    std::cout << "\nRunning " << producerNum;
    std::cout << " in parallel: \n"
              << std::endl;
    cout << "Wake up Threads\n";
    run(); // Allows threads to run

    // Sleep then exit
    sleep(time);
    /* spawn producer threads */
    for (int id = 0; id < producerNum; id++)
        producer[id].join();
    /* spawn consumer threads */
    for (int id = 0; id < producerNum; id++)
        consumer[id].join();

    cout << "\n";
    return 0;
}