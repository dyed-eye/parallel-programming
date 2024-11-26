#ifndef READERWRITER_H
#define READERWRITER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <atomic>
#include <cstdint>

class ReaderWriter {
public:
    ReaderWriter();
	~ReaderWriter();
public:
    void read();
    void write();

private:
    std::shared_mutex mtx;
    std::atomic<std::uint32_t> read_count;
};

#endif
