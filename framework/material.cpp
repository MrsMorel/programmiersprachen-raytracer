//
// Created by annetelle on 06.07.22.
//
#include "material.hpp"


std::ostream &Material::print(std::ostream &os) const {
    os<< "name: " << name_ << "\n";
    os << "color ka ambiente Reflexion: " << ka.r<< ", "<< ka.g << ", " << ka.b << "\n";
    os << "color kd diffuse Reflexion: " << kd.r<< ", "<< kd.g << ", " << kd.b << "\n";
    os << "color ks spiegelnde Reflexion: " << ks.r<< ", "<< ks.g << ", " << ks.b << "\n";
    os<< "Spekularreflexionsexponent: " << m_ << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os , Material const& material ){
    return material.print(os);
}



