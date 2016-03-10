#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iconv.h>

#include "libthaiengine/loader.h"
#include "libthaiengine/database.h"

#define BUFFER_SIZE 1023

std::vector<std::string> read_input(const char *filename){
    std::ifstream fp(filename);
    fp.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::vector<std::string> out;

    // NOT EXCEPTION SAFE!
    iconv_t ic = iconv_open("TIS-620", "UTF-8");

    while(!fp.eof()){
        fp.seekg(4, fp.cur); // "ID: "
        fp.ignore(10, ' '); // "1, "
        fp.seekg(6, fp.cur); // "Text: "

        char buffer[BUFFER_SIZE];
        fp.getline(buffer, BUFFER_SIZE);

        char iconv_buf[BUFFER_SIZE];
        size_t i_size = BUFFER_SIZE;
        size_t o_size = BUFFER_SIZE;
        char *input = buffer;
        char *output = iconv_buf;
        iconv(ic, &input, &i_size, &output, &o_size);

        out.emplace_back(iconv_buf);
    }

    iconv_close(ic);

    return out;
}

typedef std::chrono::time_point<std::chrono::high_resolution_clock> hires_clock;
#define NOW() std::chrono::high_resolution_clock::now()
#define DIFF(start) std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start).count()

int main(int argc, char* argv[])
{
    if (argc<3) {
        std::cout << "usage: " << argv[0] << " filename.dat query.txt" << std::endl;
        return 0;
    }

    hires_clock timer = NOW();

    thaiengine::Database db;
    try {
        db.load_from_file(argv[1]);
    }catch(std::exception &e){
        std::cout << "An error occured while loading database file: " << e.what() << std::endl;
        return 1;
    }
    std::vector<std::string> input;
    try{
        input = read_input(argv[2]);
    }catch(std::exception &e){
        std::cout << "An error occured while loading input file: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Initialization done in " << DIFF(timer) << "us. ";
    std::cout << "Found " << input.size() << " input items." << std::endl;

    int i = 0;
    timer = NOW();
    for(std::string item : input){
        const thaiengine::DATA_RECORD *result = db.get(item);
        if(result == nullptr){
            std::cout << "Item " << i << " not found" << std::endl;
        }else{
            std::cout << "Item " << i << " ID " << result->header.id << std::endl;
        }
        i++;
    }

    std::cout << "Search done in " << DIFF(timer) << "us. ";
}
