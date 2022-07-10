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
    float a = max().x - min().x;
    float b = max_.z - min_.z;
    float c = max_.y - min_.y;
    return 2*std::abs(a) + 2* std::abs(b) + 2* std::abs(c);
}

float Box::volume() const {
    return std::abs((max_.x - min_.x)*(max_.z - min_.z)*(max_.y - min_.y));
}



Box::Box(const glm::vec3 &min, const glm::vec3 &max, std::string name, std::shared_ptr<Material> material):
        Shape(name, material),
        min_{min},
        max_{max}{}

std::ostream &Box::print(std::ostream &os) const {
    Shape::print(os);
    os<< "minimum point, x: " << min_.x << "   y: " << min_.y << "  z: " << min_.z << "\n";
    os<< "maximum point, x: " << max_.x << "   y: " << max_.y << "  z: " << max_.z << "\n";
    os<< "area: " << area() << " square units" <<"\n";
    os<< "volume: " << volume() <<" volume units" << "\n";
    return os;
}

Box::~Box() {
}

void Box::min(const glm::vec3 &min) {
    min_ = min;
}

glm::vec3 Box::min() const {
    return min_;
}

void Box::max(const glm::vec3 &max) {
    max_ = max;
}

glm::vec3 Box::max() const {
    return max_;
}





