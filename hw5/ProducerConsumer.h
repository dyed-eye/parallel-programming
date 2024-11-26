#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

class ProducerConsumer {
public:
    ProducerConsumer();
    ~ProducerConsumer();
public:
    void produce(int item);
    int consume();

private:
    std::mutex mtx;
    std::condition_variable cv_produce;
    std::condition_variable cv_consume;
    std::queue<int> buffer;
    const int MAX_BUFFER_SIZE = 5; // Максимальный размер буфера
};

#endif // PRODUCERCONSUMER_H
