/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** maths_concepts.hpp
*/

#pragma once

#include <concepts>

namespace rtx::maths {
template <typename From, typename To>
concept non_narrowing_convertible_to =
    std::convertible_to<From, To> &&
    ((std::is_integral_v<From> && std::is_floating_point_v<To>) ||
     requires(From from) { To{from}; });

template <typename T, typename U>
concept Multiplicable = requires(T a, U b) { a* b; };

template <typename T, typename U>
    requires Multiplicable<T, U>
using multiplication_result_t = decltype(std::declval<T>() * std::declval<U>());

template <typename T, typename U>
concept Divisable = requires(T a, U b) { a / b; };

template <typename T, typename U>
    requires Divisable<T, U>
using division_result_t = decltype(std::declval<T>() / std::declval<U>());

template <typename T, typename U>
concept Addable = requires(T a, U b) { a + b; };

template <typename T, typename U>
    requires Addable<T, U>
using addition_result_t = decltype(std::declval<T>() + std::declval<U>());

template <typename T, typename U>
concept Substractable = requires(T a, U b) { a - b; };

template <typename T, typename U>
    requires Substractable<T, U>
using substraction_result_t = decltype(std::declval<T>() - std::declval<U>());
}
