#include "SimplifyLine/SimplifyLine.hpp"

namespace SimplifyLine {

template <typename T>
inline T GetSquaredDistance2D(const size_t p1, const size_t p2, const Matrix<T>& points)
{
    auto dx = points(p1, 0) - points(p2, 0);
    auto dy = points(p1, 1) - points(p2, 1);

    return dx * dx + dy * dy;
}

template <typename T, int dim>
inline T GetSquaredDistance(const size_t p1, const size_t p2, const Matrix<T>& points)
{
    T sum = 0.0;
    T temp = 0.0;
    Utility::faux_unroll<dim>::call([&](auto i) { 
        temp = points(p1, i) - points(p2, i);
        sum += temp * temp;
    });

    return sum;
}


template <typename T, int dim>
Matrix<T> SimplifyRadialDist(const Matrix<T>& points, double max_distance)
{
    const size_t rows = points.rows;
    const size_t cols = points.cols;
    const T square_distance = max_distance * max_distance;


    std::vector<T> point_buffer;
    point_buffer.reserve((points.rows * points.cols) / 2);
    Utility::faux_unroll<dim>::call([&](auto i) { point_buffer.push_back(points(0, i)); });

    size_t prev_point = 0;
    size_t next_point = 1;
    for (; next_point < rows; ++next_point)
    {
        if (GetSquaredDistance<T, dim>(next_point, prev_point, points) > square_distance)
        {
            Utility::faux_unroll<dim>::call([&](auto i) { point_buffer.push_back(points(next_point, i)); });
            prev_point = next_point;
        }
    }

    if (prev_point != next_point)
    {
        Utility::faux_unroll<dim>::call([&](auto i) { point_buffer.push_back(points(rows - 1, i)); });
    }

    size_t new_rows = point_buffer.size() / 2;
    Matrix<T> new_points(std::move(point_buffer), new_rows, 2);
    return new_points;
}

template <typename T>
Matrix<T> SimplifyRadialDist2D(const Matrix<T>& points, double max_distance)
{
    const size_t rows = points.rows;
    const size_t cols = points.cols;
    const T square_distance = max_distance * max_distance;

    // std::cout << rows << ", " << cols << std::endl;

    std::vector<T> point_buffer;
    point_buffer.reserve((points.rows * points.cols) / 2);
    point_buffer.push_back(points(0, 0));
    point_buffer.push_back(points(0, 1));

    size_t prev_point = 0;
    size_t next_point = 1;
    for (; next_point < rows; ++next_point)
    {
        if (GetSquaredDistance2D(next_point, prev_point, points) > square_distance)
        {
            point_buffer.push_back(points(next_point, 0));
            point_buffer.push_back(points(next_point, 1));
            prev_point = next_point;
        }
    }

    if (prev_point != next_point)
    {
        point_buffer.push_back(points(rows - 1, 0));
        point_buffer.push_back(points(rows - 1, 1));
    }

    size_t new_rows = point_buffer.size() / 2;
    // std::cout << new_rows  << std::endl;
    Matrix<T> new_points(std::move(point_buffer), new_rows, 2);
    return new_points;
}

template <typename T>
Matrix<T> SimplifyLine(const Matrix<T>& points, double max_distance, bool high_quality)
{
    auto new_points = SimplifyRadialDist<double, 2>(points, max_distance);


    return new_points;
}


template <typename T> 
Matrix<T> DouglasPeucker2D(const Matrix<T> &points, double max_distance)
{
    std::vector<bool> valid(points.rows);
    

}

std::string Hello(std::string& name) { return "Hello " + name; }
template <typename T>
std::vector<T> MultiplyByScalar(std::vector<T>& vec, T scalar)
{
    std::vector<T> b;
    b.reserve(vec.size());

    std::transform(vec.begin(), vec.end(), std::back_inserter(b), [scalar](auto& a_elem) { return a_elem * scalar; });

    return b;
}

// Forward declare specialization
// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl

template Matrix<double> SimplifyRadialDist<double, 2>(const Matrix<double>& points, double max_distance);
template Matrix<double> SimplifyRadialDist2D<double>(const Matrix<double>& points, double max_distance);
template Matrix<double> SimplifyLine<double>(const Matrix<double>& points, double max_distance, bool high_quality);
template std::vector<double> MultiplyByScalar<double>(std::vector<double>& vec, double scalar);
template std::vector<int> MultiplyByScalar<int>(std::vector<int>& vec, int scalar);
template std::vector<size_t> MultiplyByScalar<size_t>(std::vector<size_t>& vec, size_t scalar);

} // namespace SimplifyLine