#ifndef BARBERSHOP_H
#define BARBERSHOP_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include "Barber.h"

class BarberShop {
public:
    BarberShop(int waitingRoomSize);
    void requestHaircut(int customerId);
    void barberWork();

private:
    int waitingRoomSize;
    std::queue<int> waitingCustomers;
    std::mutex mtx;
    std::condition_variable cv;
    Barber barber;
    bool barberSleeping;
};

#endif // BARBERSHOP_H
