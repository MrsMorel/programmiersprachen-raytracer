//
// Created by annetelle on 15.06.22.
//
#include "shape.hpp"

Shape::Shape():
    name_{"default"},
    color_{255,255,255}{}

Shape::~Shape() {
}

Shape::Shape(std::string name, const Color &color) :
        name_{name}, color_{color} {}


