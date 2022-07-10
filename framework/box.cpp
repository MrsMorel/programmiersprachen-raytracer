//
// Created by annetelle on 23.06.22.
//
#include "box.hpp"
#include "shape.hpp"
#include <cmath>
#include <vector>



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

Hitpoint Box::intersect(Ray const& ray) const {
    glm::vec3 normalized_direction = glm::normalize(ray.direction);
    float t1 = (min_.x - ray.origin.x) / normalized_direction.x;
    float t2 = (min_.y - ray.origin.y) / normalized_direction.y;
    float t3 = (min_.z - ray.origin.z) / normalized_direction.z;
    float t4 = (max_.x - ray.origin.x) / normalized_direction.x;
    float t5 = (max_.y - ray.origin.y) / normalized_direction.y;
    float t6 = (max_.z - ray.origin.z) / normalized_direction.z;

    std::vector<float> distances{ t1, t2, t3, t4, t5, t6 };
    std::sort(distances.begin(), distances.end());
    for (float i : distances) {
        if (i < 0)
        {
            continue;
        }
        else {
            glm::vec3 p = ray.origin + i * normalized_direction;
            if (p.y <= max_.y && p.y >= min_.y && 
                p.z <= max_.z && p.z >= min_.z &&
                p.x <= max_.x && p.x >= min_.x) {
                
                return Hitpoint{true, i, name(), material(), p, normalized_direction};
            }
        }
    }
    return Hitpoint{};
}





