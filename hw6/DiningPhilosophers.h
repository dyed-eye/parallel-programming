#ifndef DININGPHILOSOPHERS_H
#define DININGPHILOSOPHERS_H

#include "Philosopher.h"

class DiningPhilosophers {
public:
    DiningPhilosophers(int numPhilosophers);
    ~DiningPhilosophers();
    void startDining();

private:
    int numPhilosophers;
    std::vector<Philosopher> philosophers;
    std::vector<std::mutex> forks;
    std::mutex outputMutex;
};

#endif // DININGPHILOSOPHERS_H
