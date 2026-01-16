#include <benchmark/benchmark.h>
#include "AABB.hpp"
#include <vector>
#include <random>

// Helper to generate a stable dataset
static std::vector<collision::Vector3> GeneratePoints(size_t count) {
    std::vector<collision::Vector3> points;
    points.reserve(count);
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-100.0, 100.0);
    for(size_t i = 0; i < count; ++i) {
        points.emplace_back(dist(gen), dist(gen), dist(gen));
    }
    return points;
}


static void BM_ExtendOptimized(benchmark::State& state) {
    auto points = GeneratePoints(state.range(0));
    for (auto _ : state) {
        collision::AABB box;
        for (const auto& p : points) {
            box.extend(p);
        }
        //avoid compliler optimizations
        benchmark::DoNotOptimize(box);
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
    // Each Vector3 is 3 doubles (24 bytes)
    state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(collision::Vector3));
}
BENCHMARK(BM_ExtendOptimized)->Range(1<<10, 1<<18);


static void BM_ExtendNaive(benchmark::State& state) {
    auto points = GeneratePoints(state.range(0));
    for (auto _ : state) {
        collision::AABB box;
        for (const auto& p : points) {
            box.extend_naive(p);
        }
        benchmark::DoNotOptimize(box);
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
    state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(collision::Vector3));
}
BENCHMARK(BM_ExtendNaive)->Range(1<<10, 1<<18);

BENCHMARK_MAIN();