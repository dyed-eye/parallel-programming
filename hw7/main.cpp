#include "BarberShop.h"
#include "Customer.h"

void customerThread(int id, BarberShop& shop) {
    Customer customer(id, shop);
    customer.enterShop();
}

int main() {
    const int waitingRoomSize = 3; // Size of the waiting room
    BarberShop shop(waitingRoomSize);
    
    std::thread barberThread(&BarberShop::barberWork, &shop); // Start the barber thread

    const int numCustomers = 10; // Number of customers
    std::vector<std::thread> customers;

    for (int i = 0; i < numCustomers; ++i) {
        customers.emplace_back(customerThread, i + 1, std::ref(shop)); // Create customer threads
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate time between customer arrivals
    }

    // Wait for all customer threads to finish
    for (auto& customer : customers) {
        if (customer.joinable()) {
            customer.join();
        }
    }

    // Optionally, you can join the barber thread if you want to wait for it to finish
    barberThread.join();

    return 0;
}
