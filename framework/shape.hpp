#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"

class Shape {
public:
    Shape();
    ~Shape();
    Shape(std::string name, Color const& color);
    virtual float area() const = 0;
    virtual float volume() const = 0;
    std::string name_;
    Color color_;
};
#endif

