/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Matrix.hpp
*/

#pragma once

#include <array>
#include <cstddef>
#include <ostream>
#include <stdexcept>

#include "Vector.hpp"
#include "maths_concepts.hpp"

namespace rtx::maths {
template <typename T, std::size_t R, size_t C>
    requires std::is_arithmetic_v<T>
class Matrix {
    static_assert(
        R > 0 && C > 0, "Matrix must have at least one row and one column");

   public:
    constexpr Matrix() : _data{} {}

    constexpr Matrix(std::initializer_list<T> list) {
        if (list.size() != R * C) {
            throw std::invalid_argument("Invalid size for matrix");
        }
        size_t c = 0;
        for (const auto &value : list) {
            _data.at(c++) = value;
        }
    }

    constexpr Matrix(std::initializer_list<std::initializer_list<T>> list) {
        if (list.size() != R) {
            throw std::invalid_argument("Invalid size for matrix");
        }
        size_t c = 0;
        for (const auto &row : list) {
            if (row.size() != C) {
                throw std::invalid_argument("Invalid size for matrix");
            }
            for (const auto &value : row) {
                _data.at(c++) = value;
            }
        }
    }

    T &at(const std::size_t row, const std::size_t col) {
        return _data.at(row * C + col);
    }
    [[nodiscard]] constexpr T at(
        const std::size_t row, const std::size_t col) const {
        return _data.at(row * C + col);
    }

    T &at(const std::size_t index) {
        return _data.at(index);
    }
    [[nodiscard]] constexpr T at(const std::size_t index) const {
        return _data.at(index);
    }

    template <Addable<T> U>
    constexpr Matrix<addition_result_t<T, U>, R, C> operator+(
        const Matrix<U, R, C> &m) const {
        Matrix<addition_result_t<T, U>, R, C> result;
        for (int i = 0; i < R * C; i++) {
            result.at(i) = _data.at(i) + m.at(i);
        }
        return result;
    }
    // template <NonNarrowingConvertibleTo<T> U>
    // Matrix &operator+=(const Matrix<U, R, C> &m) {
    //     for (int i = 0; i < R * C; i++) {
    //         _data.at(i) += m.at(i);
    //     }
    //     return *this;
    // }

    template <Substractable<T> U>
    constexpr Matrix<substraction_result_t<T, U>, R, C> operator-(
        const Matrix<U, R, C> &m) const {
        Matrix<substraction_result_t<T, U>, R, C> result;
        for (int i = 0; i < R * C; i++) {
            result.at(i) = _data.at(i) - m.at(i);
        }
        return result;
    }

    // template <NonNarrowingConvertibleTo<T> U>
    // Matrix &operator-=(const Matrix<U, R, C> &m) {
    //     for (int i = 0; i < R * C; i++) {
    //         _data.at(i) -= m.at(i);
    //     }
    //     return *this;
    // }

    template <Multiplicable<T> U>
    constexpr Matrix<multiplication_result_t<T, U>, R, C> operator*(U v) const {
        Matrix<multiplication_result_t<T, U>, R, C> result;
        for (int i = 0; i < R * C; i++) {
            result.at(i) = _data.at(i) * v;
        }
        return result;
    }
    // template <NonNarrowingConvertibleTo<T> U>
    // Matrix &operator*=(U v) {
    //     for (int i = 0; i < R * C; i++) {
    //         _data.at(i) *= v;
    //     }
    //     return *this;
    // }

    template <Divisable<T> U>
    constexpr Matrix<division_result_t<T, U>, R, C> operator/(U v) const {
        Matrix<division_result_t<T, U>, R, C> result;
        for (int i = 0; i < R * C; i++) {
            result.at(i) = _data.at(i) / v;
        }
        return result;
    }
    // template <NonNarrowingConvertibleTo<T> U>
    // Matrix &operator/=(U v) {
    //     for (int i = 0; i < R * C; i++) {
    //         _data.at(i) /= v;
    //     }
    //     return *this;
    // }

    template <Multiplicable<T> U, std::size_t C2>
    constexpr Matrix<multiplication_result_t<T, U>, R, C2> dot(
        const Matrix<U, C, C2> &m) const {
        Matrix<multiplication_result_t<T, U>, R, C2> result;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C2; c++) {
                result.at(r, c) = 0;
                for (int j = 0; j < C; j++) {
                    result.at(r, c) += at(r, j) * m.at(j, c);
                }
            }
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {
        for (std::size_t i = 0; i < R; i++) {
            if (i != 0) {
                os << '\n';
            }
            os << "|\t";
            for (std::size_t j = 0; j < C; j++) {
                if (j != 0) {
                    os << '\t';
                }
                os << m.at(i, j);
            }
            os << "\t|";
        }
        return os;
    }

   private:
    std::array<T, R * C> _data;
};

template <typename T, std::size_t S>
class SquareMatrix : public Matrix<T, S, S> {
   public:
    SquareMatrix() : Matrix<T, S, S>() {}

    explicit SquareMatrix(const Matrix<T, S, S> &m) : Matrix<T, S, S>(m) {}

    constexpr SquareMatrix(std::initializer_list<std::initializer_list<T>> list)
        : Matrix<T, S, S>(list) {}

    SquareMatrix dot(const SquareMatrix m) const {
        return SquareMatrix{Matrix<T, S, S>::dot(m)};
    }

    template <std::size_t C2>
    Matrix<T, S, C2> dot(const Matrix<T, S, C2> &m) const {
        return {Matrix<T, S, S>::dot(m)};
    }

    static constexpr SquareMatrix identity() {
        SquareMatrix result;
        for (int i = 0; i < S; i++) {
            result.at(i, i) = 1;
        }
        return result;
    }
};

template <typename T>
constexpr SquareMatrix<T, 4> translation_matrix(const Vector3<T> &p) {
    return {{1, 0, 0, p.x()}, {0, 1, 0, p.y()}, {0, 0, 1, p.z()}, {0, 0, 0, 1}};
}

template <typename T>
constexpr SquareMatrix<T, 4> rotation_matrix(const Vector3<T> &axis, T angle) {
    T c = std::cos(angle);
    T s = std::sin(angle);
    T t = 1 - c;
    T x = axis.x();
    T y = axis.y();
    T z = axis.z();

    return {
        {t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0},
        {t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0},
        {t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0},
        {0, 0, 0, 1}};
}

template <typename T>
constexpr SquareMatrix<T, 4> scale_matrix(const Vector3<T> &s) {
    return {{s.x(), 0, 0, 0}, {0, s.y(), 0, 0}, {0, 0, s.z(), 0}, {0, 0, 0, 1}};
}

template <typename T>
constexpr SquareMatrix<T, 4> rotation_x_matrix(T angle) {
    T c = std::cos(angle);
    T s = std::sin(angle);
    return {{1, 0, 0, 0}, {0, c, -s, 0}, {0, s, c, 0}, {0, 0, 0, 1}};
}

template <typename T>
constexpr SquareMatrix<T, 4> rotation_y_matrix(T angle) {
    T c = std::cos(angle);
    T s = std::sin(angle);
    return {{c, 0, s, 0}, {0, 1, 0, 0}, {-s, 0, c, 0}, {0, 0, 0, 1}};
}

template <typename T>
constexpr SquareMatrix<T, 4> rotation_z_matrix(T angle) {
    T c = std::cos(angle);
    T s = std::sin(angle);
    return {{c, -s, 0, 0}, {s, c, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

template <typename T>
constexpr SquareMatrix<T, 4> rotation_xyz_matrix(T x, T y, T z) {
    return rotation_x_matrix(x)
        .dot(rotation_y_matrix(y))
        .dot(rotation_z_matrix(z));
}

template <typename T>
constexpr Vector3<T> matrix_to_vector(Matrix<T, 4, 1> m) {
    return {m.at(0, 0), m.at(1, 0), m.at(2, 0)};
}

template <typename T>
constexpr Vector2<T> matrix_to_vector(Matrix<T, 3, 1> m) {
    return {m.at(0, 0), m.at(1, 0)};
}

template <typename T>
class Point3;

template <typename T>
Point3<T> matrix_to_point(const Matrix<T, 4, 1> &m) {
    return {m.at(0, 0), m.at(1, 0), m.at(2, 0)};
}
}  // namespace rtx::maths
