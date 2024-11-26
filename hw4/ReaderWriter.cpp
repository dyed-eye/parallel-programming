#include "ReaderWriter.h"

ReaderWriter::ReaderWriter() : read_count(0) {}
ReaderWriter::~ReaderWriter() {}

void ReaderWriter::read()
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    ++read_count;
    std::cout << "Reader " << std::this_thread::get_id() << " is reading. Current read count: " << read_count << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate reading
    --read_count;
    std::cout << "Reader " << std::this_thread::get_id() << " finished reading. Current read count: " << read_count << std::endl;
}

void ReaderWriter::write()
{
    std::unique_lock<std::shared_mutex> lock(mtx);
    std::cout << "Writer " << std::this_thread::get_id() << " is writing." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate writing
    std::cout << "Writer " << std::this_thread::get_id() << " finished writing." << std::endl;
}
