#include "SimplifyLine/SimplifyLine.hpp"
#include <stack>

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
Matrix<T> SimplifyRadialDist(const Matrix<T>& points, T max_distance)
{
    size_t rows = points.rows;
    const size_t cols = points.cols;
    const T square_distance = max_distance * max_distance;

    std::vector<T> point_buffer;
    point_buffer.reserve((rows * cols) / 2);
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

    size_t new_rows = point_buffer.size() / dim;
    Matrix<T> new_points(std::move(point_buffer), new_rows, dim);
    return new_points;
}

template <typename T>
Matrix<T> SimplifyRadialDist2D(const Matrix<T>& points, T max_distance)
{
    const size_t rows = points.rows;
    const size_t cols = points.cols;
    const T square_distance = max_distance * max_distance;

    // std::cout << rows << ", " << cols << std::endl;

    std::vector<T> point_buffer;
    point_buffer.reserve((rows * cols) / 2);
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

template <typename T, int dim>
Matrix<T> SimplifyLine(const Matrix<T>& points, T max_distance, bool high_quality)
{
    if (static_cast<size_t>(dim) != points.cols)
    {
        throw std::invalid_argument("Matrix dimension of 'points' is incorrect! Expected a " + std::to_string(dim) +
                                    "D line but got a " + std::to_string(points.cols) + "D line");
    }
    if (high_quality)
    {
        return DouglasPeucker<T, dim>(points, max_distance);
    }
    else
    {
        auto new_points = SimplifyRadialDist<T, dim>(points, max_distance);
        auto simplified_points = DouglasPeucker<T, dim>(new_points, max_distance);
        return simplified_points;
    }
}

template <typename T>
T inline GetSquareDistanceLineSegment2D(const Matrix<T>& points, const size_t& point, const size_t& start,
                                        const size_t& end, const T& seg_vec_x, const T& seg_vec_y, const T& seg_dot_seg)
{
    const auto point_vec_x = points(point, 0) - points(start, 0);
    const auto point_vec_y = points(point, 1) - points(start, 1);
    const auto point_dot_seg = point_vec_x * seg_vec_x + point_vec_y * seg_vec_y;
    T dist = 0.0;
    if (point_dot_seg <= 0.0)
    {
        dist = point_vec_x * point_vec_x + point_vec_y * point_vec_y;
    }
    else if (seg_dot_seg <= point_dot_seg)
    {
        const auto dx = points(point, 0) - points(end, 0);
        const auto dy = points(point, 1) - points(end, 1);
        dist = dx * dx + dy * dy;
    }
    else
    {
        const auto b = point_dot_seg / seg_dot_seg;
        const auto dx = point_vec_x - b * seg_vec_x;
        const auto dy = point_vec_y - b * seg_vec_y;
        dist = dx * dx + dy * dy;
    }
    return dist;
}

template <typename T>
T inline GetSquareDistanceLineSegment3D(const Matrix<T>& points, const size_t& point, const size_t& start,
                                        const size_t& end, const T& seg_vec_x, const T& seg_vec_y, const T& seg_vec_z,
                                        const T& seg_dot_seg)
{
    const auto point_vec_x = points(point, 0) - points(start, 0);
    const auto point_vec_y = points(point, 1) - points(start, 1);
    const auto point_vec_z = points(point, 2) - points(start, 2);
    const auto point_dot_seg = point_vec_x * seg_vec_x + point_vec_y * seg_vec_y * point_vec_z * seg_vec_z;
    ;
    T dist = 0.0;
    if (point_dot_seg <= 0.0)
    {
        dist = point_vec_x * point_vec_x + point_vec_y * point_vec_y + point_vec_z * point_vec_z;
    }
    else if (seg_dot_seg <= point_dot_seg)
    {
        const auto dx = points(point, 0) - points(end, 0);
        const auto dy = points(point, 1) - points(end, 1);
        const auto dz = points(point, 2) - points(end, 2);
        dist = dx * dx + dy * dy + dz * dz;
    }
    else
    {
        const auto b = point_dot_seg / seg_dot_seg;
        const auto dx = point_vec_x - b * seg_vec_x;
        const auto dy = point_vec_y - b * seg_vec_y;
        const auto dz = point_vec_z - b * seg_vec_z;
        dist = dx * dx + dy * dy + dz * dz;
    }
    return dist;
}

// template <typename T, int dim>
// T inline GetSquareDistanceLineSegment(const Matrix<T> &points, const size_t &point, const size_t &start, const size_t
// &end,
//                                       const std::array<T, dim> &seg_vec, const T &seg_dot_seg)
// {
//     std::array<T, dim> point_vec;
//     Utility::faux_unroll<dim>::call([&](auto i) { point_vec[i] = points(point, i) - points(start, i); });
//     T point_dot_seg = 0.0;
//     Utility::faux_unroll<dim>::call([&](auto i) { point_dot_seg += point_vec[i] * seg_vec[i]; });
//     T dist = 0.0;
//     if (point_dot_seg <= 0.0)
//     {
//         Utility::faux_unroll<dim>::call([&](auto i) { dist += point_vec[i] * point_vec[i]; });
//     }
//     else if (seg_dot_seg <= point_dot_seg)
//     {
//         std::array<T, dim> dd;
//         Utility::faux_unroll<dim>::call([&](auto i) { dd[i] = points(point, i) - points(end, i); });
//         Utility::faux_unroll<dim>::call([&](auto i) { dist += dd[i] * dd[i]; });
//     }
//     else
//     {
//         const auto b = point_dot_seg / seg_dot_seg;
//         std::array<T, dim> dd;
//         Utility::faux_unroll<dim>::call([&](auto i) { dd[i] = points(point, i) - b * seg_vec[i]; });
//         Utility::faux_unroll<dim>::call([&](auto i) { dist += dd[i] * dd[i]; });
//     }
//     return dist;
// }

template <typename T>
void RecursiveDP2D(const Matrix<T>& points, std::vector<bool>& valid, size_t start, size_t end, T max_distance)
{
    size_t segment_length = end - start;
    if (segment_length <= 1)
    {
        return;
    }

    T const seg_vec_x = points(end, 0) - points(start, 0);
    T const seg_vec_y = points(end, 1) - points(start, 1);
    T const seg_dot_seg = seg_vec_x * seg_vec_x + seg_vec_y * seg_vec_y;

    size_t point = start + 1;
    T max_point_dist = -1.0;
    std::size_t max_dist_index = start + 1;
    for (; point < end; ++point)
    {
        T dist = GetSquareDistanceLineSegment2D(points, point, start, end, seg_vec_x, seg_vec_y, seg_dot_seg);
        if (max_point_dist < dist)
        {
            max_point_dist = dist;
            max_dist_index = point;
        }
    }

    if (max_distance < max_point_dist)
    {
        // std::cout << "max_dist_index: " << max_dist_index << "; max_point_dist: " << max_point_dist << ";
        // max_distance: " << max_distance << std::endl;
        valid[max_dist_index] = true;
        RecursiveDP2D(points, valid, start, max_dist_index, max_distance);
        RecursiveDP2D(points, valid, max_dist_index, end, max_distance);
    }

    return;
}

template <typename T>
void RecursiveDP3D(const Matrix<T>& points, std::vector<bool>& valid, size_t start, size_t end, T max_distance)
{
    size_t segment_length = end - start;
    if (segment_length <= 1)
    {
        return;
    }

    T const seg_vec_x = points(end, 0) - points(start, 0);
    T const seg_vec_y = points(end, 1) - points(start, 1);
    T const seg_vec_z = points(end, 2) - points(start, 2);
    T const seg_dot_seg = seg_vec_x * seg_vec_x + seg_vec_y * seg_vec_y + seg_vec_z * seg_vec_z;

    size_t point = start + 1;
    T max_point_dist = -1.0;
    std::size_t max_dist_index = start + 1;
    for (; point < end; ++point)
    {
        T dist =
            GetSquareDistanceLineSegment3D(points, point, start, end, seg_vec_x, seg_vec_y, seg_vec_z, seg_dot_seg);
        if (max_point_dist < dist)
        {
            max_point_dist = dist;
            max_dist_index = point;
        }
    }

    if (max_distance < max_point_dist)
    {
        // std::cout << "max_dist_index: " << max_dist_index << "; max_point_dist: " << max_point_dist << ";
        // max_distance: " << max_distance << std::endl;
        valid[max_dist_index] = true;
        RecursiveDP2D(points, valid, start, max_dist_index, max_distance);
        RecursiveDP2D(points, valid, max_dist_index, end, max_distance);
    }
    return;
}

template <typename T, int dim = 2>
Matrix<T> DouglasPeucker(const Matrix<T>& points, T max_distance)
{
    const size_t rows = points.rows;
    const size_t cols = points.cols;
    std::vector<bool> valid(rows, false);
    valid[0] = true;
    valid[rows - 1] = true;
    const T square_distance = max_distance * max_distance;

    // Recursively identify all valid points
    if (dim == 2)
    {
        RecursiveDP2D(points, valid, 0, rows - 1, square_distance);
    }
    else
    {
        RecursiveDP3D(points, valid, 0, rows - 1, square_distance);
    }

    // Fill in array
    const size_t new_rows = static_cast<size_t>(std::count(valid.begin(), valid.end(), true));
    Matrix<T> simplified_points(new_rows, cols);
    size_t simplified_index = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        if (valid[i])
        {
            Utility::faux_unroll<dim>::call([&](auto j) { simplified_points(simplified_index, j) = points(i, j); });
            simplified_index++;
        }
    }

    return simplified_points;
}

// Forward declare specialization
// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl
template Matrix<double> SimplifyRadialDist2D<double>(const Matrix<double>& points, double max_distance);
template Matrix<double> SimplifyLine<double, 2>(const Matrix<double>& points, double max_distance, bool high_quality);
template Matrix<double> SimplifyLine<double, 3>(const Matrix<double>& points, double max_distance, bool high_quality);
template Matrix<float> SimplifyLine<float, 2>(const Matrix<float>& points, float max_distance, bool high_quality);
template Matrix<float> SimplifyLine<float, 3>(const Matrix<float>& points, float max_distance, bool high_quality);
template Matrix<double> SimplifyRadialDist<double, 2>(const Matrix<double>& points, double max_distance);
template Matrix<double> SimplifyRadialDist<double, 3>(const Matrix<double>& points, double max_distance);
template Matrix<float> SimplifyRadialDist<float, 2>(const Matrix<float>& points, float max_distance);
template Matrix<float> SimplifyRadialDist<float, 3>(const Matrix<float>& points, float max_distance);

} // namespace SimplifyLine