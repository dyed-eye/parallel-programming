#include "TimeSumThread.h"

TimeSumThread::TimeSumThread() : running(false) {}

void TimeSumThread::start() {
    if (!running) {
        running = true;
        thrd = std::thread(&TimeSumThread::run, this);
    }
}

void TimeSumThread::stop() {
    running = false;
    if (thrd.joinable()) {
        thrd.join();
    }
}

void TimeSumThread::add(int value) {
    std::lock_guard<std::mutex> lock(mtx);
    array.push_back(value);
}

void TimeSumThread::remove(int value) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::remove(array.begin(), array.end(), value);
    array.erase(it, array.end());
}

void TimeSumThread::run() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(30));
        std::lock_guard<std::mutex> lock(mtx);
        auto current_time = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(current_time);
        std::cout << "Current time: " << std::ctime(&time)
                  << "Sum: " << sum() << std::endl;
    }
}

int TimeSumThread::sum() {
    int total = 0;
    for (int value : array) {
        total += value;
    }
    return total;
}
