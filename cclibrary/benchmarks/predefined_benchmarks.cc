// google benchmark
#include <benchmark/benchmark.h>

// cc library
#include "../cclibrary.h"
using namespace CC;


#include <vector>
#include <limits>
#include <random>
#include <algorithm>


static void BM_orangepenguin_CC_alg_dijkstraPath_01(benchmark::State& state)
{
  // Setup
  BitBoard board;

  // The test loop
  while (state.KeepRunning())
    alg::dijkstraPath(board, BitPos{4}, BitPos{54});
}
BENCHMARK(BM_orangepenguin_CC_alg_dijkstraPath_01)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN()
