#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <iconv.h>
#include <cstring>
#include "farmhash.h"

#define HEADER_SIZE 12 - sizeof(uint32_t)
#define TIME_SIZE sizeof(int64_t)
#define TEXT_SIZE 1023

// chrono utilities
#define NOW() std::chrono::high_resolution_clock::now()
#define DIFF(start) std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start).count()
typedef std::chrono::time_point<std::chrono::high_resolution_clock> hires_clock;

int main(const int argc, const char* argv[])
{
    std::ios::sync_with_stdio(false);
    if (argc<3) {
        std::cout << "usage: " << argv[0] << " filename.dat query.txt" << '\n';
        return 0;
    }

    hires_clock timer = NOW();

    // read database file
    std::unordered_map<size_t, uint32_t> database;

    {
        std::ifstream fp(argv[1], std::ios::binary);
        fp.seekg(256, fp.beg);

        uint32_t id;
        fp.read((char*) &id, sizeof(id));

        fp.seekg(HEADER_SIZE + TIME_SIZE, fp.cur);

        int seek_size = TIME_SIZE + 4;
        {
            int32_t check_buffer;
            fp.read((char*) &check_buffer, sizeof(check_buffer));

            if(check_buffer != 0){
                // 32 bit file
                fp.seekg(-sizeof(check_buffer), fp.cur);
                seek_size = sizeof(int32_t);
            }
        }

        while(!fp.fail()){
            char buffer[TEXT_SIZE];
            fp.getline(buffer, TEXT_SIZE, 0);
            size_t hash = NAMESPACE_FOR_HASH_FUNCTIONS::Hash(buffer, strnlen(buffer, TEXT_SIZE));
            database.insert({hash, id});

            fp.read((char*) &id, sizeof(id));
            fp.seekg(HEADER_SIZE + seek_size, fp.cur);
        }
    }

    // read input
    std::vector<size_t> input;
    {
        std::ifstream fp(argv[2]);

        const iconv_t ic = iconv_open("TIS-620", "UTF-8");

        while(!fp.eof()){
            fp.seekg(4, fp.cur); // "ID: "
            fp.ignore(10, ' '); // "1, "
            fp.seekg(6, fp.cur); // "Text: "

            char buffer[TEXT_SIZE];
            fp.getline(buffer, TEXT_SIZE);

            char iconv_buf[TEXT_SIZE];
            size_t i_size = TEXT_SIZE;
            size_t o_size = TEXT_SIZE;
            char *input_ptr = buffer;
            char *output = iconv_buf;
            iconv(ic, &input_ptr, &i_size, &output, &o_size);

            size_t hash = NAMESPACE_FOR_HASH_FUNCTIONS::Hash(iconv_buf, strnlen(iconv_buf, TEXT_SIZE));
            input.emplace_back(hash);
        }

        iconv_close(ic);
    }

    std::cout << "Initialization done in " << DIFF(timer) << "us. ";
    std::cout << "Found " << input.size() << " input items." << '\n';

    int i = 0;
    timer = NOW();
    const auto end = database.end();
    for(size_t item : input){
        const auto result = database.find(item);
        if(result != end){
            std::cout << "Item " << i << " ID " << result->second << '\n';
        }else{
            std::cout << "Item " << i << " not found" << '\n';
        }
        i++;
    }

    std::cout << "Search done in " << DIFF(timer) << "us. ";
}
