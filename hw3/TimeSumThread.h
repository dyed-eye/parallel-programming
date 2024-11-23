#ifndef TIMSUMTHREAD_H
#define TIMSUMTHREAD_H

#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <condition_variable>


class TimeSumThread {
public:
    TimeSumThread();
	~TimeSumThread();
    void start();
    void stop();
    void add(int value);
    void remove(int value);

private:
    void run();
    int sum();

private:
    std::vector<int> array;
    std::thread thrd;
    std::mutex mtx;
	std::condition_variable cv;
	std::atomic<std::uint32_t> sum;
};

#endif 
