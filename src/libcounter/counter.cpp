#include "counter.h"

namespace counter {

Counter::Counter(thaiengine::Loader *ldr) : loader(ldr) {}

unsigned int Counter::count() {
    return loader->read_all().size();
}

}