#include "ProducerConsumer.h"

ProducerConsumer::ProducerConsumer() {}

ProducerConsumer::~ProducerConsumer() {}

void ProducerConsumer::produce(int item)
{
    std::unique_lock<std::mutex> lock(mtx);
    cv_produce.wait(lock, [this]() { return buffer.size() < MAX_BUFFER_SIZE; });
    buffer.push(item);
    std::cout << "Produced: " << item << std::endl;
    cv_consume.notify_all();
}

int ProducerConsumer::consume()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv_consume.wait(lock, [this]() { return !buffer.empty(); });
    int item = buffer.front();
    buffer.pop();
    std::cout << "Consumed: " << item << std::endl;
    cv_produce.notify_all();
    return item;
}
