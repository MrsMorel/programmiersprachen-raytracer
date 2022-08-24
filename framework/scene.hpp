//
// Created by annetelle on 10.07.22.
//
#include <glm/vec3.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <vector>
#include "material.hpp"
#include "shape.hpp"

#ifndef SCENE_HPP
#define SCENE_HPP
struct Scene{
    std::map<std::string, std::shared_ptr<Material>> material_map;
    std::vector<std::shared_ptr<Shape>> shape_vector;
    //std::vector<std::shared_ptr<Light>> light_vector;

};
Scene sdfParser(std::string const& file_path);
#endif //SCENE_HPP
