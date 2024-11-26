#include "ReaderWriter.h"
#include <vector>

void reader(ReaderWriter& rw)
{
    for (int i = 0; i < 5; ++i) {
        rw.read();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Interval between reads
    }
}

void writer(ReaderWriter& rw)
{
    for (int i = 0; i < 3; ++i) {
        rw.write();
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Interval between writes
    }
}

int main()
{
    ReaderWriter rw;
    std::vector<std::thread> threads;
    // Create reader threads
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(reader, std::ref(rw));
    }
    // Create writer threads
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(writer, std::ref(rw));
    }
    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}
