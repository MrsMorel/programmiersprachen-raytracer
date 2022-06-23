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
int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
