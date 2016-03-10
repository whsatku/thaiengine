#include "loader.h"

#define TEXT_SIZE 1023

namespace thaiengine {

Loader::Loader(const char* filename)
{
    size_algo = nullptr;

    fp.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        fp.open(filename, std::ios::binary);
    } catch (std::exception e) {
        throw std::invalid_argument("cannot open file");
    }

    fp.seekg(256, fp.beg);
}

DATA_RECORD Loader::read()
{
    DATA_RECORD record;
    fp.read((char*) &record.header, sizeof(record.header));

    if(size_algo != nullptr){
        goto *size_algo;
    }

time_detect:
    // seek past 64 bit timestamp
    fp.seekg(8, fp.cur);

    // check for 0000 after timestamp
    int32_t check_buffer;
    fp.read((char*) &check_buffer, sizeof(check_buffer));

    fp.seekg(-8-4, fp.cur);

    if (check_buffer == 0) {
        size_algo = &&time_64;
    } else {
        size_algo = &&time_32;
    }
    goto *size_algo;

time_64:
    fp.read((char*) &record.timestamp, sizeof(int64_t));
    fp.seekg(4, fp.cur);
    goto read_text;

time_32:
    int32_t timestamp;
    fp.read((char*) &timestamp, sizeof(timestamp));
    record.timestamp = (int64_t) timestamp;
    goto read_text;

read_text:
    char buffer[TEXT_SIZE];
    fp.getline(&buffer[0], TEXT_SIZE, 0);

    record.text = std::string(buffer);

    return record;
}
} // namespace thaiengine
