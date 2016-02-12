#include "loader.h"
#include <fstream>
#include <iconv.h>
#include <iostream>

#define TIME_DETECT 0
#define TIME_64 1
#define TIME_32 2
#define TEXT_SIZE 1023

namespace thaiengine {

Loader::Loader(char* filename)
{
    time_size = TIME_DETECT;

    fp.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        fp.open(filename, std::ios::binary);
    } catch (std::exception e) {
        throw std::invalid_argument("cannot open file");
    }

    fp.seekg(0, fp.end);
    size = fp.tellg();

    skip_header();
}

void Loader::skip_header()
{
    fp.seekg(256, fp.beg);
}

DATA_RECORD Loader::read()
{
    DATA_RECORD record;
    fp.read((char*) &record.header, sizeof(record.header));

    // detect
    if (time_size==TIME_DETECT) {
        time_detect();
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

    fp.getline(record.text, TEXT_SIZE, 0);

    return record;
}

int Loader::time_detect()
{
    fp.seekg(8, fp.cur);
    int success = 1;
    for (int i = 0; i<4; i++) {
        if (fp.get()!=0) {
            success = 0;
            fp.seekg(4-i, fp.cur);
            break;
        }
    }
    if (success==1) {
        time_size = TIME_64;
    } else {
        time_size = TIME_32;
    }
    fp.seekg(-8-4, fp.cur);

    return time_size;
}

bool Loader::has_more()
{
    return size-fp.tellg()!=0;
}

DATA_RECORD::DATA_RECORD() {
    text = new char[TEXT_SIZE];
}
DATA_RECORD::~DATA_RECORD() {
    delete[] text;
}

char* DATA_RECORD::utf8()
{
    return utf8(iconv_open("UTF8", "CP874"));
}

char* DATA_RECORD::utf8(iconv_t charset) {
    char *buffer = new char[TEXT_SIZE];
    size_t inLeft = TEXT_SIZE;
    size_t outLeft = TEXT_SIZE;
    char *input = &text[0];
    char *output = &buffer[0];
    iconv(charset, &input, &inLeft, &output, &outLeft);

    return buffer;
}

} // namespace thaiengine
