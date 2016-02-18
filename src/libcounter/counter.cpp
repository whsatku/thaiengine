#include "counter.h"

namespace counter {

Counter::Counter(thaiengine::Loader *ldr) : loader(ldr) {}

int Counter::count() {
    int result = 0;
    while(loader->has_more()){
        loader->read();
        result++;
    }
    return result;
}

}