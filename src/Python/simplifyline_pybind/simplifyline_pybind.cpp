
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

    m.def("simplify_radial_dist_2d", &SimplifyLine::SimplifyRadialDist<double, 2>, "points"_a, "max_distance"_a,
          "Simplifies a 2D using only radial distance");
    docstring::FunctionDocInject(m, "simplify_radial_dist_2d",
                                 {{"points", "The points matrix"},
                                  {"max_distance", "Maximum distance for simplification"}});

    m.def("simplify_line_3d", &SimplifyLine::SimplifyLine<double, 3>, "points"_a, "max_distance"_a, "high_quality"_a = false,
          "Simplifies a 3D Line");
    docstring::FunctionDocInject(m, "simplify_line_3d",
                                 {{"points", "The points matrix"},
                                  {"max_distance", "Maximum distance for simplification"},
                                  {"high_quality", "Preserve high quality"}});

    m.def("simplify_radial_dist_3d", &SimplifyLine::SimplifyRadialDist<double, 3>, "points"_a, "max_distance"_a,
          "Simplifies a 3D using only radial distance");
    docstring::FunctionDocInject(m, "simplify_radial_dist_3d",
                                 {{"points", "The points matrix"},
                                  {"max_distance", "Maximum distance for simplification"}});

    m.def("get_simplifyline_version", &SimplifyLine::GetSimplifyLineVersion, "Get SimplifyLine Version");
}