#include "Philosopher.h"

Philosopher::Philosopher(int id, sem_t* leftFork, sem_t* rightFork, std::mutex& outputMutex)
    : id(id), leftFork(leftFork), rightFork(rightFork), outputMutex(outputMutex) {}
	
Philosopher::~Philosopher() {}

void Philosopher::dine()
{
    while (true) {
        think();
        sem_wait(leftFork); // Берем левую вилку
        sem_wait(rightFork); // Берем правую вилку
        eat();
        sem_post(rightFork); // Освобождаем правую вилку
        sem_post(leftFork); // Освобождаем левую вилку
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
