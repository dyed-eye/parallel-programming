#ifndef READERWRITER_H
#define READERWRITER_H

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <atomic>
#include <cstdint>

class Storage {
	public:
	    Storage() = default;
	    ~Storage() = default;

		void set(std::string news);
		std::string get();
	private:
		std::string name;
    std::shared_mutex mtx;
		
};

class ReaderWriter {
public:
    ReaderWriter();
	~ReaderWriter();
public:
    void read();
    void write();

private:
	Storage strg;
    std::atomic<std::uint32_t> read_count;
};

#endif
