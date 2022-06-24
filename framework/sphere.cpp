//
// Created by annetelle on 23.06.22.
//
#include "sphere.hpp"
#include <cmath>
#include <glm/vec3.hpp>

Sphere::Sphere():
    Shape(),
    center_{0.0f, 0.0f, 0.0f},
    radius_{1.0f} {}
Sphere::Sphere(const glm::vec3 &center, float radius):
    Shape(),
    center_{center},
    radius_{std::abs(radius)} {}

float Sphere::area() const {
    return 4 * M_PI * (radius_ * radius_) ;
}

float Sphere::volume() const {
    return  M_PI * 4/3 * (radius_*radius_*radius_);
}

Sphere::Sphere(const glm::vec3 &center, float radius, std::string name, const Color &color):
    Shape(name, color),
    center_{center},
    radius_{std::abs(radius)} {}



