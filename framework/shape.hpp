#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <memory>
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include <algorithm>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/intersect.hpp>
#include "epsilon.hpp"

class Shape {
public:
    Shape();
    virtual ~Shape();
    Shape(std::string name, std::shared_ptr<Material>  material);
    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual std::ostream& print(std::ostream& os ) const;

    void              name(std::string const& name);
    std::string       name() const;
    void           material(std::shared_ptr<Material> const& mat);
    std::shared_ptr<Material>      material() const;

    virtual Hitpoint intersect(Ray const& ray) const = 0;

    void translate(glm::vec3 const& point);
    void rotate(float& degree, glm::vec3 const& point);
    void scale(glm::vec3 const& point);

    //private
private:
    std::string name_;
    std::shared_ptr<Material> material_;
    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;
};
std::ostream& operator<<(std::ostream& os, Shape const& s);

Ray transformRay(glm::mat4 const& mat, Ray const& ray);
glm::vec3 transformPoint(glm::mat4 const& mat, glm::vec3 const& point);
glm::vec3 transformVector(glm::mat4 const& mat, glm::vec3 const& vector);
void transformBack(Hitpoint const& Hitpoint, glm::mat4 const& mat);

#endif

