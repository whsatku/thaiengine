#include <iostream>
#include "libthaiengine/loader.h"
#include "libcounter/counter.h"

int main(int argc, char* argv[])
{
    if (argc<2) {
        std::cout << "usage: " << argv[0] << " filename.dat" << std::endl;
        return 0;
    }

    thaiengine::Loader loader(argv[1]);
    counter::Counter counter(&loader);

    std::cout << "Loaded " << counter.count() << " entries \\o/" << std::endl;

    return 0;
}
