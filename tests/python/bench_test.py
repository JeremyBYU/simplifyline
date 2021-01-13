import pytest
import numpy as np
from simplifyline import MatrixDouble, simplify_line_2d, simplify_line_3d, simplify_radial_dist_2d

from simplification.cutil import simplify_coords

def test_example1_simplifyline_lowquality(benchmark, example1):
    mat = MatrixDouble(example1)
    result = benchmark(simplify_line_2d, mat, 0.1, False)

def test_example1_simplifyline_lowquality(benchmark, example1):
    mat = MatrixDouble(example1)
    result = benchmark(simplify_line_2d, mat, 0.1, False)

def test_example1_simplifyline(benchmark, example1):
    mat = MatrixDouble(example1)
    result = benchmark(simplify_line_2d, mat, 0.1, True)

def test_example1_simplification(benchmark, example1):
    result = benchmark(simplify_coords, example1, 0.1)

# @pytest.mark.parametrize("max_distance", [0.1, 1.0, 10.0])
# @pytest.mark.parametrize("high_quality", [True, False])
# def test_bench_example1_simplifyline_parmetersweep(benchmark, example1,max_distance, high_quality):
#     # benchmark something
#     mat = MatrixDouble(example1)
#     result = benchmark(simplify_line_2d, mat, max_distance, high_quality)

