#pragma once
#include <mutex>
#include <condition_variable>
#include <iostream>

using std::cout;
using std::endl;


class Semaphore {
public:
    // Takes in a count, if the user decides to put one in.
    Semaphore(int count_ = 0)
        : count(count_)
    {
    }

    void notify();
    void wait();

private:
    // Creates a mutex, a condition variable and a count to create a semaphore. The condition variable allows for signalling, and the mutex stops
    // code from running.
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

// Adapted from this link, with only small changes:
// https://riptutorial.com/cplusplus/example/30142/semaphore-cplusplus-11
