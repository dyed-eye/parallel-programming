#include "TimeSumThread.h"

TimeSumThread::TimeSumThread() : stopRequested(false) {}

TimeSumThread::~TimeSumThread() {
    stop();
}

void TimeSumThread::start() {
    if (thrd.joinable()) {
        return; // Thread is already running
    }
    stopRequested = false;
    thrd = std::thread(&TimeSumThread::run, this);
}

void TimeSumThread::stop() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        stopRequested = true; // Request to stop
    }
    cv.notify_all(); // Notify the thread to wake up if it's waiting
    if (thrd.joinable()) {
        thrd.join();
    }
}

void TimeSumThread::add(int value) {
    std::lock_guard<std::mutex> lock(mtx);
    array.push_back(value);
    cv.notify_all(); // Notify the thread that a new value has been added
}

void TimeSumThread::remove(int value) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::remove(array.begin(), array.end(), value);
    array.erase(it, array.end());
    cv.notify_all(); // Notify the thread that a value has been removed
}

void TimeSumThread::run() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::seconds(5), [this] { return stopRequested; });

        if (stopRequested) {
            break; // Exit the loop if stop is requested
        }

        auto current_time = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(current_time);

        std::cout << "Current time: " << std::ctime(&time)
                  << "Sum: " << sum() << std::endl;
    }
}

int TimeSumThread::sum() {
    std::lock_guard<std::mutex> lock(mtx);
    int total = 0;
    for (int value : array) {
        total += value;
    }
    return total;
}