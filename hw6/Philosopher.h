#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <semaphore.h>

class Philosopher {
public:
    Philosopher(int id, sem_t* leftFork, sem_t* rightFork, std::mutex& outputMutex);
	~Philosopher();
    void dine();

private:
    int id; // Идентификатор философа
    sem_t* leftFork; // Левая вилка
    sem_t* rightFork; // Правая вилка
	std::mutex& outputMutex;
private:
    void think();
    void eat();
};

#endif // PHILOSOPHER_H
