//
// Created by annetelle on 04.07.22.
//

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include "color.hpp"

struct Material {
    std::string name_;
    Color ka{0,0,0}; //ambient
    Color kd{0,0,0}; //diffuse
    Color ks{0,0,0}; //punktlicht (spekular)
    float m_ = 1.0f; //Spekularreflexionsexponente: Oberfläche rau oder glatt

    std::ostream& print(std::ostream& os ) const;


};
#endif //MATERIAL_HPP
std::ostream& operator<<( std::ostream& os, Material const& material);