/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone.cpp
*/

#include "Cone.hpp"

namespace rtx::shapes {
std::optional<render::Hitpoint> Cone::hit(const maths::Ray3<double> &ray) const {
    return hit_surface(ray);
}

const render::Material &Cone::material() const {
    return _material;
}

maths::Vector3<double> Cone::getNormal(maths::Point3<double> p, maths::Point3<double> apex) const {
    maths::Vector3 a = p.vectorTo(apex);
    maths::Vector3 b = p.vectorTo(_position);
    maths::Vector3<double> c = a.cross(b);
    maths::Vector3<double> d = a.cross(c);
    return d.normalized();
}

std::optional<render::Hitpoint> Cone::hit_surface(const maths::Ray3<double> &ray) const {
    maths::Vector3 coneDirection = -_axis;
    maths::Point3 apex = _position - coneDirection;
    double coneHeight = coneDirection.norm();
    coneDirection = coneDirection.normalized();

    const double a =
        ray.direction().dot(ray.direction()) - (1 + _radius * _radius / (coneHeight * coneHeight)) *
                                                   pow(ray.direction().dot(coneDirection), 2);
    double b = 2 * (ray.direction().dot(apex.vectorTo(ray.origin())) -
                    (1 + _radius * _radius / (coneHeight * coneHeight)) *
                        ray.direction().dot(coneDirection) *
                        apex.vectorTo(ray.origin()).dot(coneDirection));
    double c = apex.vectorTo(ray.origin()).dot(apex.vectorTo(ray.origin())) -
               (1 + _radius * _radius / (coneHeight * coneHeight)) *
                   pow(apex.vectorTo(ray.origin()).dot(coneDirection), 2);

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return {};
    }

    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double y1 = (ray.at(t1) - apex).dot(coneDirection);
    bool hitSide1 = (t1 > 0 && y1 >= 0 && y1 <= coneHeight);
    if (hitSide1) {
        return render::Hitpoint{ray, t1, ray.at(t1), getNormal(ray.at(t1), apex), *this};
    }

    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    double y2 = (ray.at(t2) - apex).dot(coneDirection);
    bool hitSide2 = (t2 > 0 && y2 >= 0 && y2 <= coneHeight);
    if (!hitSide2) {
        return {};
    }
    double t = -1;
    if (hitSide2) {
        t = t2;
    }

    double normalRayDir = _axis.dot(ray.direction());
    if (normalRayDir == 0) {
        return render::Hitpoint{ray, t2, ray.at(t2), getNormal(ray.at(t2), apex), *this};
    }

    return render::Hitpoint{ray, t, ray.at(t), getNormal(ray.at(t), apex), *this};
}
}  // namespace rtx::shapes
