# Simplify 2D and 3D Lines

[![PyPI](https://img.shields.io/pypi/v/simplifyline.svg)](https://pypi.org/project/simplifyline/)
![Run Tests](https://github.com/JeremyBYU/simplifyline/workflows/Run%20Tests/badge.svg)
[![Docs](https://img.shields.io/badge/API-docs-blue)](https://jeremybyu.github.io/simplifyline/)
[![License](https://img.shields.io/pypi/l/simplifyline.svg)](https://github.com/JeremyBYU/simplifyline/blob/master/LICENSE)

A high performance 2D and 3D line simplification algorithm. Uses [Ramer-Douglas-Peucker Line Simplification](https://en.wikipedia.org/wiki/Ramer%E2%80%93Douglas%E2%80%93Peucker_algorithm).

## Key Features

* Simplify 2D and 3D lines 
* Written in C++ with python bindings. Can be used standalone in a C++ project with CMake as well.
* Based on high-performance [Simplify.js](https://mourner.github.io/simplify-js/) 

## Install with Python and Use

The python library can be installed as so:

1. `pip install simplifyline`

Example Use:

```python
from simplifyline import simplify_line_2d, MatrixDouble 
mat2D = MatrixDouble([[0.0, 0.0], [1.0, 1.0], [2.0, 2.0], [3.0, 3.0]])
results_mat2D = simplify_line_2d(mat2D, max_distance=0.1, high_quality=True)
results = np.array(results_mat2D)
np.testing.assert_array_equal(results, np.array([[0.0, 0.0], [3.0, 3.0]]))
```

See [documentation](https://jeremybyu.github.io/simplifyline/) for more details.

## Build Project Manually

You can build the project manually in two ways: using python `setup.py`, or in pure CMake

### Build Manually with Python

The root directory [setup.py](setup.py) file has been modified to build with CMake. This is meant for python users that need to build manually (for some reason) but are not actively developing or changing the code.

1. Install [conda](https://conda.io/projects/conda/en/latest/) or create a python virtual environment ([Why?](https://medium.freecodecamp.org/why-you-need-python-environments-and-how-to-manage-them-with-conda-85f155f4353c)). I recommend conda for Windows users.
2. `pip install .` - Call from root directory

### Build Manually With CMake

Building happens entirely with CMake. This is meant really only for the library developers who are working on C++ and Python in an edit-compile cycle.

#### C++ Library

1. `mkdir cmake-build && cd cmake-build` 
2. `cmake ..` -  Note - For windows also add `-DCMAKE_GENERATOR_PLATFORM=x64` 
3. `cmake --build . -j$(nproc) --config Release`

Build options:

```text
SPL_BUILD_BENCHMARKS:BOOL=ON // SPL - Build Benchmarks
SPL_BUILD_EXAMPLES:BOOL=ON // SPL - Build Examples
SPL_BUILD_PYMODULE:BOOL=ON // SPL -Build Python Module
SPL_BUILD_TESTS:BOOL=ON // SPL - Build Tests
SPL_BUILD_WERROR:BOOL=OFF // SPL - Add Werror flag to build (turns warnings into errors)
SPL_WITH_OPENMP:BOOL=ON // SPL - Build with OpenMP Support
```

#### Python Extension

This is meant for advanced python users who are actively developing the extension.

1. Install [conda](https://conda.io/projects/conda/en/latest/) or create a python virtual environment ([Why?](https://medium.freecodecamp.org/why-you-need-python-environments-and-how-to-manage-them-with-conda-85f155f4353c)). I recommend conda for Windows users.
2. Perform `CMake` build as described above
3. `cd cmake-build && cmake --build . --target python-package --config Release` 
4. `cd lib/python_package &&  pip install -e .` . This installs the library in develop/edit mode. To update the python extension in your python virtual environment all you need to do is run step 3 again.
