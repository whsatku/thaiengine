#include <iostream>
#include <iconv.h>
#include "loader.h"

int main(int argc, char* argv[])
{
    if (argc<2) {
        std::cout << "usage: " << argv[0] << " filename.dat" << std::endl;
        return 0;
    }
    thaiengine::Loader loader(argv[1]);

    iconv_t charset = iconv_open("UTF8", "CP874");

    while (loader.has_more()) {
        thaiengine::DATA_RECORD record = loader.read();
        std::cout << "id " << record.header.id << " mapfilepos " << record.header.map_file_pos << std::endl;
        char* text = record.utf8(charset);
        std::cout << text << std::endl << std::endl;
        delete[] text;
    }

    return 0;
}
