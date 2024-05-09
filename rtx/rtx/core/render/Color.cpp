/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Color.cpp
*/

#include "Color.hpp"

namespace rtx::render {

Color::Color(double r, double g, double b) : _r{r}, _g{g}, _b{b} {}

double &Color::r() {
    return _r;
}

double &Color::g() {
    return _g;
}

double &Color::b() {
    return _b;
}

double Color::r() const {
    return _r;
}

double Color::g() const {
    return _g;
}

double Color::b() const {
    return _b;
}

Color Color::operator*(double v) const {
    return {_r * v, _g * v, _b * v};
}

Color Color::operator*(const Color &c) const {
    return {_r * c._r, _g * c._g, _b * c._b};
}

Color Color::fromNormal(maths::Vector3<double> normal) {
    return {
        (normal.x() + 1) * 0.5,
        (normal.z() + 1) * 0.5,
        (normal.y() + 1) * 0.5,
    };
}

std::tuple<double, double, double> Color::toTuple() const {
    return {_r, _g, _b};
}

Color Color::operator+(const Color &c) const {
    return {_r + c._r, _g + c._g, _b + c._b};
}

Color Color::operator/(const double v) const {
    return {_r / v, _g / v, _b / v};
}

Color Color::sky(const double t) {
    const auto a = 0.5 * (t + 1);
    return (1 - a) * Color(1, 1, 1) + a * Color(0.5, 0.7, 1.);
}

std::ostream &operator<<(std::ostream &os, const Color &c) {
    return os << static_cast<u_int8_t>(c.r() * 255.999) << static_cast<u_int8_t>(c.g() * 255.999)
              << static_cast<u_int8_t>(c.b() * 255.999);
}

Color operator*(const double v, const Color &c) {
    return c * v;
}

}  // namespace rtx::render
