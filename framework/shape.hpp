#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <memory>
#include "color.hpp"
#include "material.hpp"

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

//private
private:
    std::string name_;
    std::shared_ptr<Material> material_;
};
std::ostream& operator<<( std::ostream& os , Shape const& s );
#endif

