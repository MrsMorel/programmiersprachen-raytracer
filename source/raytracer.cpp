#include "window.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "renderer.hpp"
//#include "scene.hpp"

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";
  /*Scene s = sdfParser("../../source/example1.sdf");
    for (const auto& element : s.material_map) {
        std::cout << element.first << "  aaaa " << "\n";
    }*/
  Renderer renderer{image_width, image_height, filename};
    std::cout << "test " << "\n";
  //renderer.render();

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
