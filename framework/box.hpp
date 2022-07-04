//
// Created by annetelle on 23.06.22.
//

#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Box: public Shape {
public:
    Box();
    ~Box() override;
    Box(glm::vec3 const& min, glm::vec3 const& max);
    Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color const& color);

    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream& os ) const override;
    void           min(glm::vec3 const& min);
    glm::vec3       min() const;
    void           max(glm::vec3 const& max);
    glm::vec3       max() const;
//private
private:
    glm::vec3 min_;
    glm::vec3 max_;

};
#endif //BOX_HPP
//5.5
/* override in Vererbung
 * wenn weggelassen:
 */