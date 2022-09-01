//
// Created by annetelle on 15.06.22.
//
#include "shape.hpp"

#include <memory>

Shape::Shape():
    name_{"default"},
    material_{std::make_shared<Material> (Material{})}
    {}


Shape::~Shape() {
    //std::cout << "Shape destructor " << name_ << "\n";
}

Shape::Shape(std::string name, std::shared_ptr<Material> material) :
    name_{ name }, 
    material_{ std::move(material) } {}

std::ostream &Shape::print(std::ostream &os) const {
    std::cout << "\n";
    os<< "name: " << name_ << "     material: " << material_->name_<< "\n";
    return os;
}

void Shape::name(const std::string &name) {
    name_ = name;
}

std::string Shape::name() const {
    return name_;
}

void Shape::material(const std::shared_ptr<Material> &mat) {
    material_ = mat;
}

std::shared_ptr<Material> Shape::material() const {
    return material_;
}

std::ostream& operator<<(std::ostream& os , Shape const& s )
{
    return s.print(os);
}

glm::vec3 transformPoint(glm::mat4 const& mat, glm::vec3 const& point) {
    glm::vec4 new_point {point, 1.0f };
    new_point = new_point * mat;
    return glm::vec3{ new_point };
}

glm::vec3 transformVector(glm::mat4 const& mat, glm::vec3 const& vector) {
    glm::vec4 new_vector{vector, 0.0f };
    new_vector = new_vector * mat;
    return glm::vec3{ new_vector };
}

Ray transformRay(glm::mat4 const& mat, Ray const& ray) {
    return Ray{ transformPoint(mat, ray.origin),
        glm::normalize(transformVector(mat, ray.direction)) };
}


