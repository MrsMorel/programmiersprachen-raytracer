//
// Created by annetelle on 23.06.22.
//
#include "sphere.hpp"
#include <cmath>


Sphere::Sphere():
    Shape(),
    center_{0.0f, 0.0f, 0.0f},
    radius_{1.0f} {}
Sphere::Sphere(const glm::vec3 &center, float radius):
    Shape(),
    center_{center},
    radius_{std::abs(radius)} {}

float Sphere::area() const {
    return 4 * glm::pi<float>() * (radius_ * radius_) ;
}

float Sphere::volume() const {
    return  glm::pi<float>() * 4/3 * (radius_*radius_*radius_);
}

Sphere::Sphere(const glm::vec3 &center, float radius, std::string name, std::shared_ptr<Material> material):
    Shape(name, material),
    center_{center},
    radius_{std::abs(radius)} {}

std::ostream &Sphere::print(std::ostream &os) const {
    Shape::print(os);
    os<< "center point, x: " << center_.x << "   y: " << center_.y << "  z: " << center_.z << "\n";
    os<< "radius: " << radius_ << "\n";
    os<< "area: " << area() << " square units" <<"\n";
    os<< "volume: " << volume() <<" volume units" << "\n";
    return os;
}

Hitpoint Sphere::intersect(const Ray &ray) const {
    float t = 1.0f;
    bool hit = glm::intersectRaySphere(ray.origin, glm::normalize(ray.direction), center_ , radius_*radius_, t);
    return Hitpoint{hit, t, name(), material(), ray.origin + (t * ray.direction), glm::normalize(ray.direction)};
}

Sphere::~Sphere() {
   // std::cout << "Sphere destruct " << name() << "\n";
}

void Sphere::center(const glm::vec3 &ctr) {
    center_ = ctr;
}

glm::vec3 Sphere::center() const {
    return center_;
}

void Sphere::radius(float r) {
    radius_ = r;
}

float Sphere::radius() const {
    return radius_;
}




