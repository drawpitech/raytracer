/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Matrix.hpp
*/

#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>

#include "maths_concepts.hpp"

namespace rtx::maths {

template <typename T, std::size_t R, size_t C>
class Matrix {
    static_assert(
        R > 0 && C > 0, "Matrix must have at least one row and one column");

   public:
    Matrix() : _data{} {}

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
    const T &at(const std::size_t row, const std::size_t col) const {
        return _data.at(row * C + col);
    }

    T &at(const std::size_t index) {
        return _data.at(index);
    }
    const T &at(const std::size_t index) const {
        return _data.at(index);
    }

    template <Addable<T> U>
    Matrix<addition_result_t<T, U>, R, C> operator+(
        const Matrix<U, R, C> &m) const {
        Matrix<addition_result_t<T, U>, R, C> result;
        for (int i = 0; i < R * C; i++) {
            result.at(i) = _data.at(i) + m.at(i);
        }
        return *this;
    }
    template <NonNarrowingConvertibleTo<T> U>
    Matrix &operator+=(const Matrix<U, R, C> &m) {
        for (int i = 0; i < R * C; i++) {
            _data.at(i) += m.at(i);
        }
        return *this;
    }

    template <Substractable<T> U>
    Matrix<substraction_result_t<T, U>, R, C> operator-(
        const Matrix<U, R, C> &m) const {
        Matrix<substraction_result_t<T, U>, R, C> result;
        for (int i = 0; i < R * C; i++) {
            result.at(i) = _data.at(i) - m.at(i);
        }
        return *this;
    }
    template <NonNarrowingConvertibleTo<T> U>
    Matrix &operator-=(const Matrix<U, R, C> &m) {
        for (int i = 0; i < R * C; i++) {
            _data.at(i) -= m.at(i);
        }
        return *this;
    }

    template <Multiplicable<T> U>
    Matrix<multiplication_result_t<T, U>, R, C> operator*(U v) const {
        Matrix<multiplication_result_t<T, U>, R, C> result;
        for (int i = 0; i < R * C; i++) {
            result.at(i) = _data.at(i) * v;
        }
        return *this;
    }
    template <NonNarrowingConvertibleTo<T> U>
    Matrix &operator*=(U v) {
        for (int i = 0; i < R * C; i++) {
            _data.at(i) *= v;
        }
        return *this;
    }

    template <Divisable<T> U>
    Matrix<division_result_t<T, U>, R, C> operator/(U v) const {
        Matrix<division_result_t<T, U>, R, C> result;
        for (int i = 0; i < R * C; i++) {
            result.at(i) = _data.at(i) / v;
        }
        return *this;
    }
    template <NonNarrowingConvertibleTo<T> U>
    Matrix &operator/=(U v) {
        for (int i = 0; i < R * C; i++) {
            _data.at(i) /= v;
        }
        return *this;
    }

    template <Multiplicable<T> U, std::size_t C2>
    Matrix<multiplication_result_t<T, U>, R, C> dot(
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
    requires std::is_arithmetic_v<T>
class SquareMatrix : public Matrix<T, S, S> {
   public:
    SquareMatrix() : Matrix<T, S, S>() {}

    explicit SquareMatrix(const Matrix<T, S, S> &m) : Matrix<T, S, S>(m) {}

    static constexpr SquareMatrix identity() {
        SquareMatrix result;
        for (int i = 0; i < S; i++) {
            result.at(i, i) = 1;
        }
        return result;
    }
};
}  // namespace rtx::maths
