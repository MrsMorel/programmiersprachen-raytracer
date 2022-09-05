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
/*
void Shape::translate(glm::vec3 const& point) {
    world_transformation_ = glm::translate(world_transformation_, point);
    world_transformation_inv_ = glm::inverse(world_transformation_);
}
*/
void Shape::translate(glm::vec3 const& point) {
    glm::mat4 translation_matrix =
    { 1.0f, 0.0f, 0.0f, point.x,
    0.0f, 1.0f, 0.0f, point.y,
    0.0f, 0.0f, 1.0f, point.z,
    0.0f, 0.0f, 0.0f, 1.0f };

    world_transformation_ = world_transformation_ * translation_matrix;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate(float& degree, glm::vec3 const& point) {
    world_transformation_ = glm::rotate(world_transformation_, degree, point);
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::scale(glm::vec3 const& point) {
    world_transformation_ = glm::scale(world_transformation_, point);
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

//Weltkoordinatensystem ->  lokales Objektkoordinatensystem
glm::vec3 transformPoint(glm::mat4 const& mat, glm::vec3 const& point) {
    glm::vec4 new_point{ point, 1.0f };
    new_point = new_point * glm::inverse(mat);
    return glm::vec3{ new_point };
}

glm::vec3 transformVector(glm::mat4 const& mat, glm::vec3 const& vector) {
    glm::vec4 new_vector{ vector, 0.0f };
    new_vector = new_vector * glm::inverse(mat);
    return glm::vec3{ new_vector };
}

Ray transformRay(glm::mat4 const& mat, Ray const& ray) {
    return Ray{ transformPoint(mat, ray.origin),
        glm::normalize(transformVector(mat, ray.direction)) };
}

//lokales Objektkoordinatensystem -> Weltkoordinatensystem
void transformBack(Hitpoint& hitpoint, glm::mat4 const& mat) {
    hitpoint.point = glm::vec3{ glm::vec4{ hitpoint.point,1.0f }*mat };
    hitpoint.normal = glm::normalize(glm::vec3{ glm::vec4{ hitpoint.normal, 0.0f }*glm::transpose(glm::inverse(mat)) });
}

glm::mat4 Shape::world_transformation() const {
    return world_transformation_;
}

void Shape::update_world_transformation(glm::mat4 const& mat) {
    world_transformation_ = world_transformation_ * mat;
    world_transformation_inv_ = glm::inverse(world_transformation_);
}

