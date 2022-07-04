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


void Shape::name(const std::string &name) {
    name_ = name;
}

std::string Shape::name() const {
    return name_;
}

void Shape::color(const Color &clr) {
    color_ = clr;
}

Color Shape::color() const {
    return color_;
}

std::ostream& operator<<(std::ostream& os , Shape const& s )
{
    return s.print(os);
}


