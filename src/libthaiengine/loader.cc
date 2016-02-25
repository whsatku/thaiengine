#include "loader.h"

#define TIME_DETECT 0
#define TIME_64 1
#define TIME_32 2
#define TEXT_SIZE 1023

namespace thaiengine {

Loader::Loader(const char* filename)
{
    time_size = TIME_DETECT;

    fp.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        fp.open(filename, std::ios::binary);
    } catch (std::exception e) {
        throw std::invalid_argument("cannot open file");
    }

    skip_header();
}

inline void Loader::skip_header()
{
    fp.seekg(256, fp.beg);
}

DATA_RECORD Loader::read()
{
    DATA_RECORD record;
    fp.read((char*) &record.header, sizeof(record.header));

    // detect
    if (time_size==TIME_DETECT) {
        time_size = time_detect();
    }

    switch (time_size) {
    case TIME_64:
        fp.read((char*) &record.timestamp, sizeof(int64_t));
        fp.seekg(4, fp.cur);
        break;
    case TIME_32:
        int32_t timestamp;
        fp.read((char*) &timestamp, sizeof(timestamp));
        record.timestamp = (int64_t) timestamp;
    }

    char buffer[TEXT_SIZE];
    fp.getline(&buffer[0], TEXT_SIZE, 0);

    record.text = std::string(buffer);

    return record;
}

int Loader::time_detect()
{
    // seek past 64 bit timestamp
    fp.seekg(8, fp.cur);

    // check for 0000 after timestamp
    int32_t buffer;
    fp.read((char*) &buffer, sizeof(buffer));

    fp.seekg(-8-4, fp.cur);

    if (buffer == 0) {
        return TIME_64;
    } else {
        return TIME_32;
    }
}
} // namespace thaiengine
