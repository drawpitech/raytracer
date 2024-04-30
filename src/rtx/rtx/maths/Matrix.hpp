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

namespace rtx::maths {

template <typename T, std::size_t R, size_t C>
class Matrix {
    static_assert(
        R > 0 && C > 0, "Matrix must have at least one row and one column");

   public:
    constexpr Matrix(std::initializer_list<T> list) {
        if (list.size() != R * C) {
            throw std::invalid_argument("Invalid size for matrix");
        }
        auto current = list.begin();
        for (std::size_t i = 0; i < R * C; i++) {
            _data[i] = *current++;
        }
    }

    T &at(std::size_t row, std::size_t col) {
        return _data.at(row * C + col);
    }
    const T &at(std::size_t row, std::size_t col) const {
        return _data.at(row * C + col);
    }

    T &operator()(std::size_t index) {
        return _data[index];
    }
    const T &operator()(std::size_t index) const {
        return _data[index];
    }

    Matrix operator+(const Matrix &m) const {

        for (int i = 0; i < R * C; i++) {
            _data.at(i) += m.at(i);
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {
        for (std::size_t i = 0; i < R; i++) {
            if (i != 0) {
                os << ' ';
            }
            for (std::size_t j = 0; j < C; j++) {
                os << m.at(i, j);
            }
            os << '\n';
        }
        return os;
    }

   private:
    std::array<T, R * C> _data;
};

}  // namespace rtx::maths
