//
// Created by annetelle on 26.08.22.
//

#ifndef LIGHT_HPP
#define LIGHT_HPP
struct Light{
    std::string name;
    glm::vec3 pos = {0.0f, 0.0f, 0.0f};
    Color color = {0.0f, 0.0f, 0.0f};
    float brightness = 0.0f;
};
#endif //LIGHT_HPP
