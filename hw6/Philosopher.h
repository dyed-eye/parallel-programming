#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

class Philosopher {
public:
    Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork, std::mutex& outputMutex);
    ~Philosopher();
    void dine();

private:
    int id; // Идентификатор философа
    std::mutex& leftFork; // Левая вилка
    std::mutex& rightFork; // Правая вилка
    std::mutex& outputMutex;

private:
    void think();
    void eat();
};

#endif // PHILOSOPHER_H
