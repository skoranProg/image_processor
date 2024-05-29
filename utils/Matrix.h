//
// Created by skoran on 10/10/2023.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace image_processor::utils {

/**
 * Represents a matrix of Ts.
 */
template <typename T>
class Matrix {
public:
    class Row {
        friend class Matrix;

    public:
        T& operator[](size_t j) {
            return parent_->GetEl(number_, j);
        }

        const T& operator[](size_t j) const {
            return parent_->GetEl(number_, j);
        }

    protected:
        Row(size_t number, Matrix* parent) : number_{number}, parent_{parent} {
        }

        size_t number_;
        Matrix* parent_;
    };

    class ConstRow {
        friend class Matrix;

    public:
        const T& operator[](size_t j) const {
            return parent_->GetEl(number_, j);
        }

    protected:
        ConstRow(size_t number, const Matrix* parent) : number_{number}, parent_{parent} {
        }

        size_t number_;
        const Matrix* parent_;
    };

public:
    Matrix() : Matrix(0, 0) {
    }

    Matrix(size_t m, size_t n, T def = T());

    template <size_t n, size_t m>
    explicit Matrix(const std::array<std::array<T, n>, m>& data);

    Matrix(const Matrix& origin);

    Matrix(Matrix&& rhs) noexcept;

    ~Matrix();

    Matrix& operator=(const Matrix& rhs);

    Matrix& operator=(Matrix&& rhs) noexcept;

    Row operator[](size_t i) {
        Row r(i, this);
        return r;
    }

    ConstRow operator[](size_t i) const {
        ConstRow r(i, this);
        return r;
    }

    T& GetEl(size_t i, size_t j) {
        return data_[Offset(i, j)];
    }

    const T& GetEl(size_t i, size_t j) const {
        return data_[Offset(i, j)];
    }

    /// returns number of rows of matrix
    size_t GetRowNum() const {
        return row_num_;
    }

    size_t GetColNum() const {
        return col_num_;
    }

    /// calculates Offset of the [i_th, j_th] element
    size_t Offset(size_t i, size_t j) const {
        return i * col_num_ + j;
    }

    Matrix<T> Transpose() const {
        Matrix<T> res(col_num_, row_num_);
        for (size_t i = 0; i < row_num_; ++i) {
            for (size_t j = 0; j < col_num_; ++j) {
                res.GetEl(j, i) = GetEl(i, j);
            }
        }
        return res;
    }

    static void Swap(Matrix& l, Matrix& r) noexcept;

protected:
    size_t row_num_;
    size_t col_num_;
    T* data_;
};

template <typename T>
template <size_t n, size_t m>
Matrix<T>::Matrix(const std::array<std::array<T, n>, m>& data) : row_num_{m}, col_num_{n}, data_{new T[n * m]} {
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            GetEl(i, j) = data[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(size_t m, size_t n, T def) {
    if ((m == 0 && n != 0) || (m != 0 && n == 0)) {
        throw std::logic_error("Invalid matrix size!");
    }
    row_num_ = m;
    col_num_ = n;
    if (m == 0) {
        data_ = nullptr;
        return;
    }
    data_ = new T[m * n];
    std::fill(data_, data_ + m * n, def);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& origin)
    : row_num_{origin.row_num_},
      col_num_{origin.col_num_},
      data_(origin.data_ ? (new T[row_num_ * col_num_]) : nullptr) {
    std::copy(origin.data_, origin.data_ + row_num_ * col_num_, data_);
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& rhs) noexcept : row_num_{rhs.row_num_}, col_num_{rhs.col_num_}, data_{rhs.data_} {
    rhs.row_num_ = 0;
    rhs.col_num_ = 0;
    rhs.data_ = nullptr;
}

template <typename T>
Matrix<T>::~Matrix() {
    delete[] data_;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Matrix tmp(rhs);
    Swap(tmp, *this);
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) noexcept {
    Swap(*this, rhs);
    return *this;
}

template <typename T>
void Matrix<T>::Swap(Matrix<T>& l, Matrix<T>& r) noexcept {
    std::swap(l.data_, r.data_);
    std::swap(l.col_num_, r.col_num_);
    std::swap(l.row_num_, r.row_num_);
}

}  // namespace image_processor::utils

#endif  // MATRIX_MATRIX_H
