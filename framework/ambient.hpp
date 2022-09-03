//
// Created by annetelle on 26.08.22.
//
#include "color.hpp"
#ifndef AMBIENT_HPP
#define AMBIENT_HPP
struct Ambient{
    Color color = {0.0f, 0.0f, 0.0f};
    std::string name = "ambient";

    std::ostream& operator<<(std::ostream &os) const {
        std::cout << "\n";
        os << "name: " << name << "\n";
        os << "color, r: " << color.r << "   g: " << color.g << "  b: " << color.b << "\n";
        return os;
    }
};


#endif //AMBIENT_HPP
