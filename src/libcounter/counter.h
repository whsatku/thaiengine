#include "../libthaiengine/loader.h"

#ifndef THAIENGINE_COUNTER_H
#define THAIENGINE_COUNTER_H

namespace counter {

class Counter {
public:
    Counter(thaiengine::Loader*);
    int count();
private:
    thaiengine::Loader *loader;
};

} // namespace counter

#endif //THAIENGINE_COUNTER_H
