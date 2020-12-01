#include "SimplifyLine/Types.hpp"

#include "simplifyline_pybind/simplifyline_pybind.hpp"
#include "simplifyline_pybind/types/bind_types.hpp"

namespace SimplifyLine {
// Convert Numpy Array to SimplifyLine Matrix
template <typename T>
Matrix<T> py_array_to_matrix(py::array_t<T, py::array::c_style | py::array::forcecast> array,
                                        bool copy_data = false)
{
    // return std::vector<std::array<T, dim>>();
    // std::cout << "Calling py_array_to_matrix" << std::endl;
    if (array.ndim() != 2)
    {
        throw py::cast_error("Numpy array must have exactly 2 Dimensions to be transformed to SimplifyLine::Matrix<T>");
    }
    size_t rows = array.shape(0);
    size_t cols = array.shape(1);

    if (copy_data)
    {
        size_t total_elements = rows * cols;
        std::vector<T> vectors_T(total_elements);
        // auto array_unchecked = array.mutable_unchecked<2UL>();
        size_t element_counter = 0;
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                vectors_T[element_counter] = array.at(i, j);
                element_counter++;
            }
        }
        SimplifyLine::Matrix<T> new_matrix(std::move(vectors_T), rows, cols);
        return new_matrix;
    }
    else
    {
        auto info = array.request();
        SimplifyLine::Matrix<T> new_matrix(static_cast<T*>(info.ptr), rows, cols);
        return new_matrix;
    }
}

void pybind_matrix_types(py::module_& m)
{

    py::bind_vector<std::vector<std::size_t>>(
        m, "VectorULongInt", py::buffer_protocol(),
        "Contiguous buffer of Uint64. Use np.asarray() to get to get numpy array.");
    py::bind_vector<std::vector<uint8_t>>(m, "VectorUInt8", py::buffer_protocol(),
                                          "Contiguous buffer of Uint8. Use np.asarray() to get to get numpy array.");
    py::bind_vector<std::vector<double>>(m, "VectorDouble", py::buffer_protocol(),
                                         "Contiguous buffer of Float64. Use np.asarray() to get to get numpy array.");
    py::bind_vector<std::vector<int>>(m, "VectorInt", py::buffer_protocol(),
                                      "Contiguous buffer of Int32. Use np.asarray() to get to get numpy array.");

    py::class_<SimplifyLine::Matrix<double>>(
        m, "MatrixDouble", py::buffer_protocol(),
        "Matrix (Double) representation of numpy array. Use np.asarray() to get numpy array.")
        .def(py::init<>(&py_array_to_matrix<double>), "Creates a Matrix", "points"_a, "copy"_a = false)
        .def_buffer([](SimplifyLine::Matrix<double>& m) -> py::buffer_info {
            return py::buffer_info(m.ptr,                                   /* Pointer to buffer */
                                   sizeof(double),                          /* Size of one scalar */
                                   py::format_descriptor<double>::format(), /* Python struct-style format descriptor */
                                   2UL,                                     /* Number of dimensions */
                                   {m.rows, m.cols},                        /* Buffer dimensions */
                                   {sizeof(double) * m.cols,                /* Strides (in bytes) for each index */
                                    sizeof(double)});
        });
}

} // namespace SimplifyLine
