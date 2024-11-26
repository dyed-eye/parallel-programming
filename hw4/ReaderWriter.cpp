#include "ReaderWriter.h"

void Storage::set(std::string news)
{
	std::unique_lock<std::shared_mutex> lock(mtx);
	name = news;
}

std::string Storage::get()
{
	std::shared_lock<std::shared_mutex> lock(mtx);
	return name;
}

ReaderWriter::ReaderWriter() : read_count(0) {}
ReaderWriter::~ReaderWriter() {}

void ReaderWriter::read()
{
    std::string data = strg.get();
    ++read_count;
    std::cout << "Read " << data << ". Current read count: " << read_count << std::endl;
}

void ReaderWriter::write()
{
	strg.set("hello");
    std::cout << "Writer " << std::this_thread::get_id() << " is writing." << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate writing
    //std::cout << "Writer " << std::this_thread::get_id() << " finished writing." << std::endl;
}

