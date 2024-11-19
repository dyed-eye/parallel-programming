#ifndef TIMSUMTHREAD_H
#define TIMSUMTHREAD_H

#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

class TimeSumThread {
public:
    TimeSumThread();
    void start();
    void stop();
    void add(int value);
    void remove(int value);

private:
    void run();
    int sum();

    std::vector<int> array;
    std::thread thrd;
    std::mutex mtx;
    bool running;
};

#endif // TIMSUMTHREAD_H
