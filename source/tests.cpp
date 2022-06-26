#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.cpp"
#include "box.cpp"
#include "shape.hpp"

TEST_CASE("Sphere area and volume", "sphere_area_volume") {
    Sphere s{};
    REQUIRE(s.area() == Approx(12.56637f));
    REQUIRE(s.volume() == Approx(4.18879f));
    Sphere s1{{1.0f,2.5f,-0.5f},15.5f};
    REQUIRE(s1.area() == Approx(3019.071f));
    REQUIRE(s1.volume() == Approx(15598.531f));
    Sphere s2{{1.0f,2.5f,-0.5f},-15.5f};
    REQUIRE(s2.area() == Approx(3019.071f));
    REQUIRE(s2.volume() == Approx(15598.531f));
}
TEST_CASE("Box area and volume", "box_area_volume") {
    Box b{};
    REQUIRE(b.area() == Approx(6.0f));
    REQUIRE(b.volume() == Approx(1.0f));
    Box b1{{1.0f,2.5f,-0.5f},{0.0f, 0.0f, 1.0f}};
    REQUIRE(b1.area() == Approx(10.0f));
    REQUIRE(b1.volume() == Approx(3.75f));
    Box s2{{0.0f, 0.0f, 1.0f},{1.0f,2.5f,-0.5f}};
    REQUIRE(s2.area() == Approx(10.0f));
    REQUIRE(s2.volume() == Approx(3.75f));
    Box b2{{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f}};
    REQUIRE(b2.area() == Approx(0.0f));
    REQUIRE(b2.volume() == Approx(0.0f));
}
//5.5
TEST_CASE("print Box ", "box_print") {
    Box b{};
    std::cout << b;
    Box b1{{1.0f,2.5f,-0.5f},{0.0f, 0.0f, 1.0f}};
    std::cout << b1;
    Box s2{{0.0f, 0.0f, 1.0f},{1.0f,2.5f,-0.5f}};
    std::cout << s2;
    Box b2{{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f}};
    std::cout << b2;
    Box b3{{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f}, "test box", {0,0,0}};
    std::cout << b3;

}
TEST_CASE("Sphere print", "sphere_print") {
    Sphere s{};
    std::cout << s;
    Sphere s1{{1.0f,2.5f,-0.5f},15.5f};
    std::cout << s1;
    Sphere s2{{1.0f,2.5f,-0.5f},-15.5f};
    std::cout << s2;
    Sphere s3{{1.0f,2.5f,-0.5f},-15.5f, "test sphere", {255,0,10}};
    std::cout << s3;
}
//5.6
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "ray.hpp"
TEST_CASE ( "i n t e r s e c t _ r a y _ s p h e r e " , "[intersect]" )
{
// Ray
    glm::vec3 ray_origin{0.0f , 0.0f , 0.0f };
// ray direction has to be normalized !
// you can use :
// v = glm :: normalize ( some_vector )
    glm::vec3 ray_direction{0.0f , 0.0f , 1.0f };
// Sphere
    glm::vec3 sphere_center{0.0f ,0.0f , 5.0f };
    float sphere_radius{1.0f };
    float distance = 0.0f ;
    auto result = glm::intersectRaySphere (
            ray_origin , ray_direction ,
            sphere_center ,
            sphere_radius * sphere_radius , // squared radius !!!
            distance );
    REQUIRE(distance == Approx(4.0f ));
}
//5.6
TEST_CASE ( "i n t e r s e c t _ r a y _ s p h e r e 1" , "[intersect_test1]" )
{
// Ray
    glm::vec3 ray_origin{0.0f , 0.0f , 0.0f };
// ray direction has to be normalized !
// you can use :
// v = glm :: normalize ( some_vector )
    glm::vec3 ray_direction{0.0f , 0.0f , 1.0f };
// Sphere
    glm::vec3 sphere_center{0.0f ,0.0f , 5.0f };
    float sphere_radius{1.0f };
    float distance = 0.0f ;
    auto result = glm::intersectRaySphere (
            ray_origin , ray_direction ,
            sphere_center ,
            sphere_radius * sphere_radius , // squared radius !!!
            distance );
    REQUIRE(distance == Approx(4.0f ));
    REQUIRE(result == true);

    Sphere s{};
    Ray r{ray_origin,ray_direction};
    Sphere test{sphere_center,sphere_radius, "test", {0,0,0}};
    Hitpoint hit = test.intersect(r);
    Hitpoint hit2 = s.intersect(r);
    REQUIRE(true == hit.cut);
    REQUIRE(true == hit2.cut);
    Sphere s1{{1.0f,2.5f,-0.5f},15.5f};
    Hitpoint hit3 = s1.intersect(r);
    REQUIRE(true == hit2.cut);
    Ray r2{{0.0f,0.0f,0.0f},{15.0f,0.0f,0.0f}};
    Hitpoint hit4 = s1.intersect(r2);
    Hitpoint hit5 = s.intersect(r2);
    REQUIRE(true == hit4.cut);
    REQUIRE(true == hit5.cut);
    Sphere s2{{1.0f,2.5f,-0.5f},-15.5f};
    Ray r3{{4.0f,-5.0f,0.0f},{10.0f,0.0f,-10.0f}};
    Sphere s3{{1.0f,2.5f,-0.5f},-15.5f, "test sphere", {255,0,10}};
    Hitpoint hit6 = s.intersect(r3);
    Hitpoint hit7 = s1.intersect(r3);
    Hitpoint hit8 = s2.intersect(r3);
    Hitpoint hit9 = s3.intersect(r3);
    REQUIRE(false == hit6.cut);
    REQUIRE(true == hit7.cut);
    REQUIRE(true == hit8.cut);
    REQUIRE(true == hit9.cut);

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
