import pytest
import numpy as np
from simplifyline import MatrixDouble, simplify_line_2d, simplify_line_3d


def test_basic():
    mat2D = MatrixDouble([[0.0, 0.0], [1.0, 1.0], [2.0, 2.0], [3.0, 3.0]])
    results_mat2D = simplify_line_2d(mat2D, max_distance=0.1, high_quality=True)
    results = np.array(results_mat2D)
    np.testing.assert_array_equal(results, np.array([[0.0, 0.0], [3.0, 3.0]]))

def test_example1(example1):
    mat = MatrixDouble(example1)
    results_mat = simplify_line_2d(mat, 0.1, True)
    results = np.array(results_mat)

    assert type(results) == np.ndarray
    assert results.shape == (1118, 2)

def test_exception():
    """Ensure exceptions are thrown when invalid arguments are given"""
    mat2D = MatrixDouble([[0.0, 0.0], [1.0, 1.0], [2.0, 2.0], [3.0, 3.0]])
    mat3D = MatrixDouble([[0.0, 0.0, 0.0], [1.0, 1.0, 1.0], [2.0, 2.0, 2.0], [3.0, 3.0, 3.0]])

    with pytest.raises(ValueError):
        simplify_line_2d(mat3D, 0.1, True)

    with pytest.raises(ValueError):
        simplify_line_3d(mat2D, 0.1, True)