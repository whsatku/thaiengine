#include <iostream>
#include "database.h"
#include "farmhash.h"

namespace thaiengine {
    std::size_t Hasher::operator()(const std::string text) const {
        return (std::size_t) util::Hash32(text);
    }

    void Database::add(DATA_RECORD record) {
        database.insert({record.text, record});
    }

    const DATA_RECORD* Database::get(char* key) {
        auto record = database.find(std::string(key));
        if(record == database.end()){
            return nullptr;
        }
        return &record->second;
    }

    void Database::load_from_file(char *filename) {
        Loader loader(filename);

        while(loader.has_more()){
            DATA_RECORD record = loader.read();
            add(record);
        }
#ifndef NDEBUG
        std::cout << "used " << database.bucket_count() << " buckets" << std::endl;
        std::size_t max = 0;
        for(unsigned long i = 0, j = database.bucket_count(); i < j; i++){
            std::size_t size = database.bucket_size(i);
            if(size > max){
                max = size;
            }
        }
        std::cout << "load factor " << database.max_load_factor() << " items" << std::endl;
        std::cout << "largest bucket holds " << max << " items" << std::endl;
#endif
    }
}