#include "BarberShop.h"

BarberShop::BarberShop(int waitingRoomSize)
    : waitingRoomSize(waitingRoomSize), barberSleeping(true) {}

void BarberShop::requestHaircut(int customerId)
{
    std::unique_lock<std::mutex> lock(mtx);
    if (waitingCustomers.size() < waitingRoomSize) {
        waitingCustomers.push(customerId);
        std::cout << "Customer " << customerId << " is waiting." << std::endl;
        barberSleeping = false;
        cv.notify_one(); // Wake up the barber
    } else {
        std::cout << "Customer " << customerId << " leaves (waiting room full)." << std::endl;
    }
}

void BarberShop::barberWork()
{
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !waitingCustomers.empty(); }); // Wait for customers

        int customerId = waitingCustomers.front();
        waitingCustomers.pop();
        std::cout << "Barber is serving customer " << customerId << "." << std::endl;
        lock.unlock(); // Unlock before cutting hair

        barber.cutHair(); // Simulate cutting hair

        lock.lock();
        if (waitingCustomers.empty()) {
            barberSleeping = true;
            std::cout << "Barber is sleeping." << std::endl;
        }
    }
}
