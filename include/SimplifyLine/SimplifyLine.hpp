// MIT License

// Copyright (c) 2020 Jeremy Castagno

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef SIMPLIFYLINE
#define SIMPLIFYLINE

#include "SimplifyLine/Types.hpp"
#include "SimplifyLine/Utility.hpp"

namespace SimplifyLine {

/**
 * \brief Get version of SPLIb
 * 
 * \return std::string 
 */
std::string GetSimplifyLineVersion();

/**
 * \brief Says hello with a name
 * 
 * \param name 
 * \return std::string 
 */
std::string Hello(std::string& name);

/**
 * \brief Multiplies a generic array by a scalar
 * 
 * \tparam T 
 * \param vec 
 * \param scalar 
 * \return std::vector<T> 
 */
template <typename T>
std::vector<T> MultiplyByScalar(std::vector<T>& vec, T scalar);



/**
 * \brief Will perform Douglas Peucker Simplication on the line
 * 
 * \tparam T 
 * \param points Matrix of 2D or 3D points
 * \param max_distance Maximum distance of point on line
 * \return Matrix<T> The simplified line
 */
template <typename T> 
Matrix<T> DouglasPeucker2D(const Matrix<T> &points, double max_distance);


/**
 * \brief Will simplify a 2D or 3D line
 * 
 * \tparam T 
 * \param points Matrix of 2D or 3D points
 * \param max_distance Maximum distance of point on line
 * \param high_quality Create high quality simplification, quality comes with increased computation time.
 * 
 * \return Matrix<T> The simplified line
 */
template <typename T> 
Matrix<T> SimplifyLine(const Matrix<T> &points, double max_distance, bool high_quality=true);


/**
 * \brief Will perform simple radial distance simplification on a line
 * 
 * \tparam T 
 * \param points Matrix of 2D or 3D points
 * \param max_distance Maximum distance of point on line
 * \return Matrix<T> The simplified line
 */
template <typename T> 
Matrix<T> SimplifyRadialDist2D(const Matrix<T> &points, double max_distance);

template <typename T, int dim>
Matrix<T> SimplifyRadialDist(const Matrix<T>& points, double max_distance);


} // namespace SimplifyLine

#endif