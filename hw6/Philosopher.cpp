#include "Philosopher.h"

Philosopher::Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork, std::mutex& outputMutex)
    : id(id), leftFork(leftFork), rightFork(rightFork), outputMutex(outputMutex) {}

Philosopher::~Philosopher() {}

void Philosopher::dine()
{
    while (true) {
        think();
        
        // Use unique_lock with defer_lock to avoid deadlock
        std::unique_lock<std::mutex> lock_a(leftFork, std::defer_lock);
        std::unique_lock<std::mutex> lock_b(rightFork, std::defer_lock);
        
        // Lock both forks
        std::lock(lock_a, lock_b);
        
        eat();
    }
}

void Philosopher::think()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Имитация времени размышления
    std::lock_guard<std::mutex> lock(outputMutex);
    std::cout << "Philosopher " << id << " thinks." << std::endl;
}

void Philosopher::eat()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Имитация времени еды
    std::lock_guard<std::mutex> lock(outputMutex);
    std::cout << "Philosopher " << id << " eats." << std::endl;
}
