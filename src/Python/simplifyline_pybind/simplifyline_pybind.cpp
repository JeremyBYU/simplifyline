
#include "simplifyline_pybind/simplifyline_pybind.hpp"
#include "simplifyline_pybind/docstring/docstring.hpp"

#include "simplifyline_pybind/types/bind_types.hpp"

using namespace SimplifyLine;

PYBIND11_MODULE(simplifyline_pybind, m)
{
    m.doc() = "Python binding of SimplifyLine";

    pybind_matrix_types(m);

    m.def("simplify_line", &SimplifyLine::SimplifyLine<double>, "points"_a, "max_distance"_a, "high_quality"_a = false,
          "Simplifies a 2D/3D Line");
    docstring::FunctionDocInject(m, "simplify_line",
                                 {{"points", "The points matrix"},
                                  {"max_distance", "Maximum distance for simplification"},
                                  {"high_quality", "Preserve high quality"}});

    m.def("hello", &SimplifyLine::Hello, "name"_a, "Says hello to name");
    docstring::FunctionDocInject(m, "hello", {{"name", "The name to say hello with"}});

    // You *can* use use function overload with same name, but python documentation doesn't support function overload
    // Here I choose to make multiple function with different names
    m.def("multiply_by_scalar_double", &SimplifyLine::MultiplyByScalar<double>, "vec"_a, "scalar"_a,
          "Multiplies a double vector");
    m.def("multiply_by_scalar_int", &SimplifyLine::MultiplyByScalar<int>, "vec"_a, "scalar"_a,
          "Multiplies an int vector");
    m.def("multiply_by_scalar_size_t", &SimplifyLine::MultiplyByScalar<size_t>, "vec"_a, "scalar"_a,
          "Multiplies a size_t vector");
    docstring::FunctionDocInject(
        m, "multiply_by_scalar_double",
        {{"vec", "A list of double numbers "}, {"scalar", "A scalar number to multiply the list by."}});
    docstring::FunctionDocInject(
        m, "multiply_by_scalar_int",
        {{"vec", "A list of int numbers "}, {"scalar", "A scalar number to multiply the list by."}});
    docstring::FunctionDocInject(
        m, "multiply_by_scalar_size_t",
        {{"vec", "A list of size_t numbers "}, {"scalar", "A scalar number to multiply the list by."}});

    m.def("get_simplifyline_version", &SimplifyLine::GetSimplifyLineVersion, "Get SimplifyLine Version");
    // Heres an example to overload, but the documentation is wonky
    // m.def("multiply_by_scalar", &SimplifyLine::MultiplyByScalar<double>, "vec"_a, "scalar"_a, "Multiplies a vector");
    // m.def("multiply_by_scalar", &SimplifyLine::MultiplyByScalar<int>, "vec"_a, "scalar"_a, "Multiplies a vector");
    // m.def("multiply_by_scalar", &SimplifyLine::MultiplyByScalar<size_t>, "vec"_a, "scalar"_a, "Multiplies a vector");
    // docstring::FunctionDocInject(
    //     m, "multiply_by_scalar",
    //     {{"vec", "A list of numbers (double, int, size_t)"}, {"scalar", "A scalar number to multiply the list
    //     by."}});
}