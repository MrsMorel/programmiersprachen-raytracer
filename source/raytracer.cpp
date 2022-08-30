#include "window.hpp"
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "renderer.hpp"
#include "scene.hpp"

//now single threaded again
int main(int argc, char* argv[])
{
  //Scene s = sdfParser("./example1.sdf");
  //std::cout << s.material_map.empty() << "\n";
  //std::cout << s.material_map.begin()->second << "\n";
  //material test
  /*for (const auto& element : s.material_map) {
        std::cout << element.first << "\n";
    }
*/

  auto scene = sdfParser("../source/test.sdf");
        Renderer renderer{scene.rend.width, scene.rend.height, scene.rend.filename};
        renderer.render(scene);

    Window window{{scene.rend.width, scene.rend.height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
