#include "Semaphore.h"

void Semaphore::notify()
{
    // Notifys the semaphore to increment it's own counter.
    std::unique_lock<std::mutex> lock(mtx);
    count++;
    cv.notify_one();
}

void Semaphore::wait() {
    // If the counter is equal to 0, will prevent the code from progressing any further. If it is higher than 0, it will not prevent it however it
    // will decrement the counter for when the wait function is called again.
    std::unique_lock<std::mutex> lock(mtx);
    while (count == 0) {
        cv.wait(lock);
    }
    count--;
}