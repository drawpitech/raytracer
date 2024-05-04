/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main.cpp
*/

#include <iostream>
#include <rtx/maths/Vector.hpp>
#include <rtx/maths/types.hpp>
#include <vector>

struct camera {
    rtx::maths::Point3<int> position{0, 0, 0};

    rtx::maths::Vector3<double> angle{0, 0, 0};

    rtx::maths::Vector2<double> resolution{1920, 1080};

    double fov = std::numbers::pi / 2;
};

struct sphere {
    rtx::maths::Point3<double> position{0, 0, 0};
    double radius = 0;
};

int main(int argc, char *argv[]) {
    rtx::maths::Matrix<double, 3, 3> m{{12, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto a = rtx::maths::SquareMatrix<double, 3>::identity();

    rtx::maths::SquareMatrix b(a);

    std::clog << b << '\n';

    a *= 2;

    std::clog << m << '\n' << m.dot(a);
    // camera cam{{0, 0, 0}, {0, 0, 0}, {1920, 1080}, std::numbers::pi};
    // sphere s{{3, 3, 2}, 1};
    // std::clog << cam.position << "\n";
    // std::cout << "P6\n"
    //           << cam.resolution.x() << " " << cam.resolution.y() << "\n";
    // std::cout << "255\n";
    //
    // for (int i = 0; i < 1080; i++) {
    //     for (int j = 0; j < 1920; j++) {
    //         rtx::maths::Vector2 v{
    //             cam.angle.x() + (j / cam.resolution.x() * cam.fov),
    //             cam.angle.y() + (i / cam.resolution.y() * cam.fov *
    //                              (cam.resolution.y() / cam.resolution.x())),
    //         };
    //
    //         // std::clog << v << "\n";
    //         rtx::maths::Vector3 v3{
    //             std::sin(v.x() * std::cos(v.y())),
    //             std::cos(v.x()) * std::cos(v.y()), std::sin(v.y())};
    //
    //         auto a = v3.norm();
    //         auto b = 2 * v3.dot(cam.position - s.position);
    //         auto c =
    //             (cam.position - s.position).dot(cam.position - s.position) -
    //             (s.radius * s.radius);
    //
    //         auto d = (b * b) - 4 * a * c;
    //         // std::clog << d << "\n";
    //
    //         unsigned char r = (255. / 1080.) * i;
    //         unsigned char g = (255. / 1920.) * j;
    //         unsigned char b2 = '\xFF';
    //
    //         if (d < 0) {
    //             std::cout << r << g << b2;
    //         } else {
    //             std::cout << '\0' << '\0' << '\0';
    //         }
    //     }
    // }
}
