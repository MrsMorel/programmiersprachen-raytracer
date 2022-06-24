//
// Created by annetelle on 23.06.22.
//

#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Box: public Shape {
public:
    Box();
    Box(glm::vec3 const& min, glm::vec3 const& max);
    Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color const& color);

    float area() const override;
    float volume() const override;

    glm::vec3 min_;
    glm::vec3 max_;

};
#endif //BOX_HPP
