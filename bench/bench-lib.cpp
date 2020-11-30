#include "doctest/doctest.h"
#include <nanobench.h>
#include "SimplifyLine/SimplifyLine.hpp"

#include <vector>

TEST_CASE("bench_multiply_by_scalar") {
    std::vector<double> input{0.0, 1.0, 2.0};
    double scalar = 2.0;
    ankerl::nanobench::Bench().run("mult_scalar", [&]() {
        auto output = SimplifyLine::MultiplyByScalar(input, scalar);
    });
}

