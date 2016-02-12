#ifndef THAIENGINE_READER_H_
#define THAIENGINE_READER_H_

#include <fstream>
#include <iconv.h>

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
    char* text;

    DATA_RECORD();
    ~DATA_RECORD();
    char* utf8();
    char* utf8(iconv_t);
};

class Loader {
public:
    Loader(char*);
    DATA_RECORD read();
    bool has_more();
private:
    int time_size;
    std::ifstream::pos_type size;
    std::ifstream fp;

    void skip_header();
    int time_detect();
};

} // namespace thaiengine

#endif // THAIENGINE_READER_H_
