#ifndef THAIENGINE_DATABASE_H
#define THAIENGINE_DATABASE_H

#include "loader.h"
#include <unordered_map>

namespace thaiengine {

struct Hasher {
    std::size_t operator()(const std::string text) const;
};

class Database {
    std::unordered_map<std::string, DATA_RECORD, Hasher> database;

public:
    void load_from_file(char* filename);
    void add(DATA_RECORD);
    const DATA_RECORD* get(char*);
};

}

#endif //THAIENGINE_DATABASE_H
