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

std::ostream &Sphere::print(std::ostream &os) const {
    Shape::print(os);
    os<< "center point, x: " << center_.x << "   y: " << center_.y << "  z: " << center_.z << "\n";
    os<< "radius: " << radius_ << "\n";
    os<< "area: " << (*this).area() << " square units" <<"\n";
    os<< "volume: " << (*this).volume() <<" volume units" << "\n";
    return os;
}

Hitpoint Sphere::intersect(const Ray &ray) const {
    float t = 1.0f;
    bool hit = glm::intersectRaySphere(ray.origin, glm::normalize(ray.direction), center_ , radius_*radius_, t);
    return Hitpoint{hit, t, name_, color_, ray.origin + (t * ray.direction), glm::normalize(ray.direction)};
}



