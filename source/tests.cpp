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
int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
