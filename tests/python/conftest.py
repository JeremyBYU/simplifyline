import pathlib
import pytest
import numpy as np

FIXTURES_DIR = pathlib.Path(__file__).parent / "../../fixtures"
POINTS_DIR = FIXTURES_DIR / "points"

@pytest.fixture
def example1():
    return np.load(POINTS_DIR / "example_1.npy")

