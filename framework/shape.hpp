#ifndef SHAPE_HPP
#define SHAPE_HPP

class Shape {
public:
    Shape();
    virtual ~Shape();
    virtual float area() const = 0;
    virtual float volume() const = 0;
};
#endif

