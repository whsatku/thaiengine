# ThaiEngine, C++ implementation

## Building

Building use CMake, and requires iconv. Out of tree and ninja building is recommended.

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -GNinja ..
ninja
```

To build benchmark utility, add `-DBUILD_BENCH=ON` to the cmake arguments.
