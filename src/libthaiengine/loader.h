#ifndef THAIENGINE_READER_H_
#define THAIENGINE_READER_H_

#include <cstdint>
#include <fstream>

namespace thaiengine {

class DATA_RECORD {
public:
    struct header {
      uint32_t id;
      uint16_t lang
              :2;
      uint16_t length
              :10;
      bool tail_space
              :1;
      bool is_unused
              :1;
      bool numeric
              :1;
      bool :1;
      uint32_t map_file_pos;
    } header;
    int64_t timestamp;
    std::string text;
};

class Loader {
public:
    Loader(const char*);
    DATA_RECORD read();
private:
    void* size_algo;
    std::ifstream fp;
};

} // namespace thaiengine

#endif // THAIENGINE_READER_H_
