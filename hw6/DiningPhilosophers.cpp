#include "DiningPhilosophers.h"

DiningPhilosophers::DiningPhilosophers(int numPhilosophers)
    : numPhilosophers(numPhilosophers), forks(numPhilosophers)
{
    for (int i = 0; i < numPhilosophers; ++i) {
        philosophers.emplace_back(i, forks[i], forks[(i + 1) % numPhilosophers], outputMutex);
    }
}

DiningPhilosophers::~DiningPhilosophers() {}

void DiningPhilosophers::startDining()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < numPhilosophers; ++i) {
        threads.emplace_back(&Philosopher::dine, &philosophers[i]);
    }

    // Limit execution time to 10 seconds
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Terminate all threads (not a clean exit, but for demonstration purposes)
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.detach(); // Detach threads to allow them to finish
        }
    }
}
