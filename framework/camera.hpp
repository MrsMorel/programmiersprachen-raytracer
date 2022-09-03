//
// Created by annetelle on 23.08.22.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/gtc/constants.hpp>
#include "ray.hpp"
#include <iostream>

class Camera{
public:
    Camera();
    Camera(std::string const& name, float fov_x);
    Camera(std::string const& name, float fov_x, glm::vec3 direction, glm::vec3 up);
    Ray c_ray(unsigned x, unsigned y, unsigned width, unsigned height) const;
    std::ostream& operator<<(std::ostream &os) const;

    inline std::string get_name() const {
        return name_;
    }
    inline float get_fov_x() const {
        return fov_x;
    }
    inline glm::vec3 get_eye() const {
        return eye_;
    }
    inline glm::vec3 get_direction() const {
        return direction_;
    }
    inline glm::vec3 get_up() const {
        return up_;
    }

private:
    std::string name_;
    //glm::vec3 position = {0.0f , 0.0f , 0.0f };
    float fov_x; //horizontaler öffnungswinkel, blickt in richtung der negativen z-achse
    glm::vec3 eye_; //position
    glm::vec3 direction_; //richtung der Kamera
    glm::vec3 up_;

};


#endif //CAMERA_HPP
