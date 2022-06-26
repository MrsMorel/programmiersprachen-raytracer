//
// Created by annetelle on 15.06.22.
//
#include "shape.hpp"

Shape::Shape():
    name_{"default"},
    color_{255,255,255}{}

Shape::~Shape() {
    std::cout << "Shape destructor " << name_ << "\n";
}

Shape::Shape(std::string name, const Color &color) :
        name_{name}, color_{color} {}

std::ostream &Shape::print(std::ostream &os) const {
    return os<< "name: " << name_ << "      color: " << color_ << "\n";
}
std::ostream& operator<<(std::ostream& os , Shape const& s )
{
    return s.print(os);
}


