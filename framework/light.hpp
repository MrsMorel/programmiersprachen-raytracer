//
// Created by annetelle on 26.08.22.
//

#ifndef LIGHT_HPP
#define LIGHT_HPP
struct Light{
    std::string name;
    glm::vec3 pos = {0.0f, 0.0f, 0.0f};
    Color color = {0.0f, 0.0f, 0.0f};
    float brightness = 0.5f;

    std::ostream& print(std::ostream &os) const {
        std::cout << "\n";
        os << "name: " << name << "\n";
        os << "pos, x: " << pos.x << "   y: " << pos.y << "  z: " << pos.z << "\n";
        os << "color, x: " << color.r << "   y: " << color.g << "  z: " << color.b << "\n";
        os << "brightness: " << brightness << "\n";
        return os;
    }
    std::ostream& operator<<(std::ostream& os) const
    {
        return print(os);
    }
};
#endif //LIGHT_HPP
