//
// Created by annetelle on 04.09.22.
//

#ifndef RAYTRACER_EPSILON_HPP
#define RAYTRACER_EPSILON_HPP

#define EPSILON 0.0001f

template<typename T>
inline bool between_epsilon(T min, T middle, T max){
    return (min - EPSILON) <= (middle + EPSILON) && (middle - EPSILON) <= (max + EPSILON);
}
#endif //RAYTRACER_EPSILON_HPP
