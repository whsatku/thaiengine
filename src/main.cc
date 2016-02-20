#include <iostream>
#include <chrono>
#include <iconv.h>
#include "libthaiengine/database.h"
extern "C" {
#include "rss.h"
}

void query(thaiengine::Database *db, char* query){
    auto start = std::chrono::steady_clock::now();
    const thaiengine::DATA_RECORD *record = db->get(&query[0]);
    std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;

    std::cout << "Querying " << query << " takes " << duration.count() << " s" << std::endl;
    std::cout << "Peak query RSS: " << ::getPeakRSS() << " bytes" << std::endl;

    if(record == nullptr){
        std::cout << "not found" << std::endl;
    }else {
        std::cout << "id " << record->header.id << " pos " << record->header.map_file_pos << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc<2) {
        std::cout << "usage: " << argv[0] << " filename.dat" << std::endl;
        return 0;
    }
//    iconv_t charset = iconv_open("UTF8", "CP874");

    thaiengine::Database db;

    std::cout << "Starting RSS: " << ::getCurrentRSS() << " bytes" << std::endl;

    auto start = std::chrono::steady_clock::now();
    try {
        db.load_from_file(argv[1]);
    }catch(std::exception &e){
        std::cout << "An error occured while loading input file: " << e.what() << std::endl;
        return 1;
    }
    std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;
    std::cout << "Loading takes " << duration.count() << " s" << std::endl << std::endl;
    std::cout << "Peak loading RSS: " << getPeakRSS() << " bytes" << std::endl;

    query(&db, (char *) std::string("THEFRONTVILLAGE").c_str());
    std::cout << std::endl;
    query(&db, (char *) std::string("THISVERYLONGMESSAGEWILLNOTBEFOUND").c_str());

    return 0;
}
