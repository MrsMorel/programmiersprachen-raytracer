//
// Created by annetelle on 23.06.22.
//
#include "box.hpp"
#include "shape.hpp"
#include <cmath>


Box::Box():
    Shape(),
    min_ {0.0f , 0.0f, 0.0f},
    max_ {1.0f, 1.0f , 1.0f} {}

Box::Box(const glm::vec3 &min, const glm::vec3 &max):
        Shape(),
        min_{min},
        max_{max} {}

float Box::area() const {
    float a = max_.x - min_.x;
    float b = max_.z - min_.z;
    float c = max_.y - min_.y;
    return 2*std::abs(a) + 2* std::abs(b) + 2* std::abs(c);
}

float Box::volume() const {
    return std::abs((max_.x - min_.x)*(max_.z - min_.z)*(max_.y - min_.y));
}

Box::Box(const glm::vec3 &min, const glm::vec3 &max, std::string name, const Color &color):
        Shape(name, color),
        min_{min},
        max_{max}{}



