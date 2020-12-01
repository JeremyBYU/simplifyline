#include "doctest/doctest.h"
#include <nanobench.h>
#include "SimplifyLine/SimplifyLine.hpp"
#include <chrono>
#include <vector>

using namespace std::literals::chrono_literals;

SimplifyLine::Matrix<double> generate_line_points(size_t num_points)
{
    std::vector<double> point_buffer;
    point_buffer.reserve(num_points * 2);
    double start_x = 0.0;
    double start_y = 0.0;
    double dx = 0.5;
    for (int i = 0; i < num_points; i++)
    {
        start_x += dx;
        start_y += dx;
        point_buffer.push_back(start_x);
        point_buffer.push_back(start_y);
    }
    SimplifyLine::Matrix<double> new_points(std::move(point_buffer), num_points, 2);
    return new_points;
}

// Benchmarks how fast we can get 64bit random values from Rng.
void bench_(ankerl::nanobench::Bench* bench, std::string name, size_t num_points)
{

    auto points = generate_line_points(num_points);
}

TEST_CASE("bench_simplify_2d")
{
    ankerl::nanobench::Bench bench;
    bench.title("Simplify 2D").timeUnit(1us, "us").warmup(10).minEpochIterations(2000);

    // Running the benchmark multiple times, with different number of elements
    for (auto num_points : {10U, 100U, 1000U, 10000U, 100000U})
    {
        auto points = generate_line_points(num_points);
        std::string name = std::to_string(num_points);
        bench.run(name, [&]() {
            auto results = SimplifyLine::SimplifyRadialDist2D<double>(points, 1.0);
            // std::cout << results.rows << std::endl;
            ankerl::nanobench::doNotOptimizeAway(results);
        });
    }
}


TEST_CASE("bench_simplify_2d_template")
{
    ankerl::nanobench::Bench bench;
    bench.title("Simplify 2D Template").timeUnit(1us, "us").warmup(10).minEpochIterations(2000);

    // Running the benchmark multiple times, with different number of elements
    for (auto num_points : {10U, 100U, 1000U, 10000U, 100000U})
    {
        auto points = generate_line_points(num_points);
        std::string name = std::to_string(num_points);
        bench.run(name, [&]() {
            auto results = SimplifyLine::SimplifyRadialDist<double, 2>(points, 1.0);
            // std::cout << results.rows << std::endl;
            ankerl::nanobench::doNotOptimizeAway(results);
        });
    }
}
