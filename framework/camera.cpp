//
// Created by annetelle on 28.08.22.
//
#include "camera.hpp"
Camera::Camera():
    name_{"default camera"},
    fov_x{90.0f},
    eye_{glm::vec3{}},
    direction_{0.0f,0.0f,-1.0f},
    up_{0.0f,1.0f,0.0f}
    {}

Camera::Camera(const std::string &name, float fov_x) :
        name_{name}, fov_x{fov_x}, direction_{0.0f,0.0f,-1.0f}, up_{0.0f,1.0f,0.0f}
{}
Camera::Camera(const std::string &name, float fov_x, glm::vec3 direction, glm::vec3 up) :
    name_{name}, fov_x{fov_x}, direction_{direction}, up_{up}
    {}

Ray Camera::c_ray(unsigned x, unsigned y, unsigned int width, unsigned int height) const {
    Ray ray{eye_};
    float direction = (width/2.0f) / tan(fov_x/2.0f * (glm::pi<float>() / 180.0f));
    glm::vec3 vec{x- ( width/2.0f), y- (height/2.0f), -direction};
    ray.direction = glm::normalize(direction_ + vec);
    return ray;
}
std::ostream& Camera::operator<<(std::ostream &os) const {
    std::cout << "\n";
    os<< "name: " << name_ << "\n";
    os<< "fov_x: " << fov_x << "\n";
    os<< "eye, x: " << eye_.x << "   y: " << eye_.y << "  z: " << eye_.z << "\n";
    os<< "direction, x: " << direction_.x << "   y: " << direction_.y << "  z: " << direction_.z << "\n";
    os<< "up, x: " << up_.x << "   y: " << up_.y << "  z: " << up_.z << "\n";
    return os;
}






