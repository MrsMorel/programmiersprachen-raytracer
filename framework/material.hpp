//
// Created by annetelle on 04.07.22.
//

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include "color.hpp"

struct Material {
    std::string name;
    Color ka{0.,0,0};
    Color kd{0,0,0};
    Color ks{0,0,0};
    float m = 1.0f; //Spekularreflexionsexponente: Oberfläche rau oder glatt
};
#endif //MATERIAL_HPP
