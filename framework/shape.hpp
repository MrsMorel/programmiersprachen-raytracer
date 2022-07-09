#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include <algorithm>

class Shape {
public:
    Shape();
    virtual ~Shape();
    Shape(std::string name, Color const& color);
    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual std::ostream& print(std::ostream& os ) const;
    virtual Hitpoint intersect(Ray const& ray) const = 0;

    void              name(std::string const& name);
    std::string       name() const;
    void           color(Color const& clr);
    Color       color() const;

//private
private:
    std::string name_;
    Color color_;
};
std::ostream& operator<<( std::ostream& os , Shape const& s );
#endif

