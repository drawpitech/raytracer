/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Color.hpp
*/

#pragma once
#include <rtx/maths/Vector.hpp>

namespace rtx::core {

class Color {
   public:
    Color() = default;
    Color(double r, double g, double b);

    double &r();

    double &g();

    double &b();

    [[nodiscard]] double r() const;
    [[nodiscard]] double g() const;
    [[nodiscard]] double b() const;

    static Color fromNormal(maths::Vector3<double> normal);

    [[nodiscard]] std::tuple<double, double, double> toTuple() const;

    friend std::ostream &operator<<(std::ostream &os, const Color &c);

    Color operator*(double v) const;

    friend Color operator*(double v, const Color &c);

    Color operator+(const Color &c) const;

   private:
    double _r{0};
    double _g{0};
    double _b{0};
};

Color sky(double t);

}  // namespace rtx::core
