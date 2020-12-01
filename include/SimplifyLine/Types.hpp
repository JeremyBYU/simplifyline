#ifndef SIMPLIFYLINE_TYPES
#define SIMPLIFYLINE_TYPES
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <array>

namespace SimplifyLine {

/**
 * This class is a generic matrix datastructure used to hold point data
 * It can own the data or it may not. It can also take ownserhip of a memory buffer.
 * Over time I have become concerned with this datastructure because of this flexibility which can bring bugs if one is
 * not careful...
 *
 */
template <class T>
class Matrix
{
  public:
    /** @brief Does the matrix own the data pointed to by `ptr`. If yes then ptr == data.data().  */
    bool own_data;
    /** @brief Buffer of memory that may/may-not be used based upon own_data flag  */
    std::vector<T> data;
    /** @brief This is raw pointer that never needs to be freed.
     * It either point to memory in `data` which will be automatically freed during object destruction (`own_data` =
     * true). Or it points some other managed memory controlled by the user (`own_data` = false)
     */
    T* ptr;
    /** @brief Rows in the matrix  */
    size_t rows;
    /** @brief Columns in the matrix  */
    size_t cols;

    /**
     * @brief Construct a new Matrix< T> object
     *
     * @param ptr_          Raw pointer to underlying data that Matrix DOES NOT own
     * @param rows_
     * @param cols_
     */
    Matrix<T>(T* ptr_, size_t rows_, size_t cols_) : own_data(false), data(), ptr(ptr_), rows(rows_), cols(cols_) {}
    /**
     * @brief Construct a new Matrix< T> object, with memory allocated and owned for rows*cols
     *
     */
    Matrix<T>(size_t rows_, size_t cols_)
        : own_data(true), data(rows_ * cols_, 0), ptr(data.data()), rows(rows_), cols(cols_)
    {
    }
    /**
     * @brief Construct a new Matrix< T> object, everything is empty but it is owned
     *
     */
    Matrix<T>() : own_data(true), data(), ptr(data.data()), rows(0), cols(0) {}
    /**
     * @brief Construct a new Matrix< T> object.
     * We will take ownership of this data buffer
     *
     * @param old_vector    Old vector that will moved and managed by this new Matrix Object
     * @param rows_
     * @param cols_
     */
    Matrix<T>(std::vector<T>&& old_vector, size_t rows_, size_t cols_)
        : own_data(true), data(), ptr(nullptr), rows(rows_), cols(cols_)
    {
        data = std::move(old_vector);
        ptr = data.data();
    }
    ~Matrix<T>() = default;
    /**
     * @brief Construct a new Matrix< T> object, Copy Constructor.
     * Will take an existing matrix and will perform a copy.
     * If the data is owned it will be copied, if not it wont be copied.
     * @param a
     */
    Matrix<T>(Matrix<T>& a) : own_data(a.own_data), data(a.data), ptr(a.ptr), rows(a.rows), cols(a.cols)
    {
        if (own_data)
        {
            ptr = data.data();
        }
    }
    /**
     * @brief Construct a new Matrix< T> object, Copy Constructor.
     * Will take an existing matrix and will perform a copy.
     * If the data is owned it will be copied, if not it wont be copied.
     * @param a
     */
    Matrix<T>(const Matrix<T>& a) : own_data(a.own_data), data(a.data), ptr(a.ptr), rows(a.rows), cols(a.cols)
    {
        if (own_data)
        {
            ptr = data.data();
        }
    }
    /**
     * @brief Default move constructor, take ownership of all the data of `other`
     *
     * @param other
     */
    Matrix<T>(Matrix<T>&& other) = default;

    /**
     * @brief Copy assignment operator
     * This one is a little tricky. We make a copy of every element in the data.
     * However if we own the data we reassign `ptr` to belong to our new copied buffer
     * @param a
     * @return Matrix<T>&
     */
    Matrix<T>& operator=(const Matrix<T>& a)
    {
        own_data = a.own_data;
        data = a.data;
        ptr = a.ptr;
        rows = a.rows;
        cols = a.cols;
        if (a.own_data)
        {
            ptr = data.data();
        }
        return *this;
    };

    /**
     * @brief Simple helper function to change our `ptr` to point to our own buffer
     *
     */
    void UpdatePtrFromData() { ptr = data.data(); }
    /**
     * @brief Simply updates our rows and columns and data
     *
     * @param rows_
     * @param cols_
     */
    void UpdatePtrFromData(const size_t rows_, const size_t cols_)
    {
        rows = rows_;
        cols = cols_;
        ptr = data.data();
        own_data = true;
    }

    /**
     * @brief Acces an element of the Matrix using 2D indices
     *
     * @param i
     * @param j
     * @return const T&
     */
    T& operator()(size_t i, size_t j) const
    {
        // assert(i >= 0 && i < rows);
        // assert(j >= 0 && j < cols);
        return ptr[i * cols + j];
    }
    /**
     * @brief Access an element in the matrix using its underlying buffer 1D index
     *
     * @param index
     * @return const T&
     */
    T& operator()(size_t index) const
    {
        // assert(i >= 0 && i < rows);
        // assert(j >= 0 && j < cols);
        return ptr[index];
    }

    /**
     * @brief This actually performs a memory copy from an unknown buffer of one type (G)
     * to *our* buffer of a different type (T). We own this new copied data.
     *
     * @tparam G
     * @param ptr_from
     * @param rows
     * @param cols
     * @return Matrix<T>
     */
    template <class G>
    static Matrix<T> CopyFromDifferentType(G* ptr_from, size_t rows, size_t cols)
    {
        Matrix<T> matrix;
        auto& matrix_data = matrix.data;
        auto total_elements = rows * cols;
        matrix_data.resize(total_elements);
        for (size_t i = 0; i < total_elements; ++i)
        {
            matrix_data[i] = static_cast<T>(ptr_from[i]);
        }
        matrix.UpdatePtrFromData(rows, cols);
        return std::move(matrix);
    }
};
} // namespace SimplifyLine

#endif