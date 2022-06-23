#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

class Shape {
public:
    Shape();
    ~Shape();
    virtual float area() const = 0;
    virtual float volume() const = 0;
    std::string name_;
};
#endif

