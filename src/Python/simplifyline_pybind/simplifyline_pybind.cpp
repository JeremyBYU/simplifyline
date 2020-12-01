
#include "simplifyline_pybind/simplifyline_pybind.hpp"
#include "simplifyline_pybind/docstring/docstring.hpp"

#include "simplifyline_pybind/types/bind_types.hpp"

using namespace SimplifyLine;

PYBIND11_MODULE(simplifyline_pybind, m)
{
    m.doc() = "Python binding of SimplifyLine";

    pybind_matrix_types(m);

    m.def("simplify_line_2d", &SimplifyLine::SimplifyLine<double, 2>, "points"_a, "max_distance"_a, "high_quality"_a = false,
          "Simplifies a 2D Line");
    docstring::FunctionDocInject(m, "simplify_line_2d",
                                 {{"points", "The points matrix"},
                                  {"max_distance", "Maximum distance for simplification"},
                                  {"high_quality", "Preserve high quality"}});

    m.def("simplify_line_3d", &SimplifyLine::SimplifyLine<double, 3>, "points"_a, "max_distance"_a, "high_quality"_a = false,
          "Simplifies a 3D Line");
    docstring::FunctionDocInject(m, "simplify_line_3d",
                                 {{"points", "The points matrix"},
                                  {"max_distance", "Maximum distance for simplification"},
                                  {"high_quality", "Preserve high quality"}});

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