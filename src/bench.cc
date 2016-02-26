#include <benchmark/benchmark.h>
#include <sstream>
#include "libthaiengine/database.h"

static void BM_SearchFound(benchmark::State& state) {
    thaiengine::Database database;
    database.load_from_file("SyllableDB-V1.dat");
    char search[] = "THEFRONTVILLAGE";
    char* searchQ = (char*) &search;

    while (state.KeepRunning()){
        benchmark::DoNotOptimize(database.get(searchQ));
    }
}
BENCHMARK(BM_SearchFound);

static void BM_SearchNotFound(benchmark::State& state) {
    thaiengine::Database database;
    database.load_from_file("SyllableDB-V1.dat");
    char search[] = "THISVERYLONGMESSAGEWILLNOTBEFOUND";
    char* searchQ = (char*) &search;

    while (state.KeepRunning()){
        benchmark::DoNotOptimize(database.get(searchQ));
    }
}
BENCHMARK(BM_SearchNotFound);

static void BM_FileLoad(benchmark::State& state) {
    std::ostringstream filename;
    filename << "SyllableDB-V" << state.range_x() << ".dat";
    std::string file_str = filename.str();
    const char* name = file_str.c_str();

    while (state.KeepRunning()){
        thaiengine::Database database;
        database.load_from_file(name);
    }
}
BENCHMARK(BM_FileLoad)
        ->Arg(1)
        ->Arg(2)
        ->Arg(3)
        ->MinTime(5.0);

BENCHMARK_MAIN();