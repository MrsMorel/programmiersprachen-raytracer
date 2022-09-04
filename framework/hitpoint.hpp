//
// Created by annetelle on 25.06.22.
//

#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <string>
#include "color.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

struct Hitpoint{
    bool cut = false;
    float t = 0.0f;
    std::string name = "  ";
    std::shared_ptr<Material> material{};
    glm::vec3 direction{0.0f,0.0f,0.0f};
    glm::vec3 point{0.0f,0.0f,0.0f};
    glm::vec3 normal{0.0f,0.0f,0.0f};

};
#endif //HITPOINT_HPP
