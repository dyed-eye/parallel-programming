#include "ProducerConsumer.h"

void producer(ProducerConsumer& pc)
{
    for (int i = 0; i < 10; ++i) {
        pc.produce(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Имитация времени производства
    }
}

void consumer(ProducerConsumer& pc)
{
    for (int i = 0; i < 10; ++i) {
        pc.consume();
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Имитация времени потребления
    }
}

int main()
{
    ProducerConsumer pc;

    std::thread producerThread(producer, std::ref(pc));
    std::thread consumerThread(consumer, std::ref(pc));

    producerThread.join();
    consumerThread.join();

    return 0;
}
