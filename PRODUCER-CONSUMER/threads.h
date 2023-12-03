#ifndef THREADS_H
#define THREADS_H

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
void producer()
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

    while (!quit)
    {
        while (ready)
        {
        }
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
    ready = false;
    sleep(time);
    quit = true;
}
#endif