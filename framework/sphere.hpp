//
// Created by annetelle on 23.06.22.
//

#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>
#include "hitpoint.hpp"
class Sphere: public Shape {
public:
    Sphere();
    //~Sphere();
    Sphere(glm::vec3 const& center, float radius);
    Sphere(glm::vec3 const& center, float radius, std::string name, Color const& color);
    std::ostream& print(std::ostream& os ) const override;
    Hitpoint intersect(Ray const& ray) const;

    float area() const override;
    float volume() const override;


    glm::vec3 center_;
    float radius_;

};
#endif //SPHERE_HPP