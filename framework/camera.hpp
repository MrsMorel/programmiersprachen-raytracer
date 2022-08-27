//
// Created by annetelle on 23.08.22.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/glm.hpp>

struct Camera{
    std::string name = "default camera";
    glm::vec3 position = {0.0f , 0.0f , 0.0f };
    float fov_x; //horizontaler öffnungswinkel, blickt in richtung der negaticen z-achse
    //float resolution;
    Ray c_ray(int x, int y, unsigned width, unsigned height);
};


#endif //CAMERA_HPP
