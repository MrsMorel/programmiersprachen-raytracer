//
// Created by annetelle on 23.08.22.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/glm.hpp>
#include "ray.hpp"

class Camera{
public:
    Camera();
    Camera(std::string const& name, float fov_x);
    Ray c_ray(int x, int y, unsigned width, unsigned height) const;

private:
    std::string name_;
    //glm::vec3 position = {0.0f , 0.0f , 0.0f };
    float fov_x; //horizontaler öffnungswinkel, blickt in richtung der negativen z-achse
    glm::vec3 eye_;
    glm::vec3 direction_;
    //float resolution;
    //glm::vec3 direction = {0.0f,0.0f,-1.0f}; //negativer z achse
};


#endif //CAMERA_HPP
