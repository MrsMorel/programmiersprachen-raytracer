// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
    //render checker pattern
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

void Renderer::render(const Scene &s) {
    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            Pixel p(x,y);
           // Ray ray{s.camera.position,};
            // TODO render fertigstellen
            // p.color = trace(ray, s);
            write(p);

        }
    }
    ppm_.save(filename_);
}

Color Renderer::trace(const Ray &ray, const Scene &s) {
    std::shared_ptr<Shape> closest_o;
    Hitpoint closest_t;
    for (const auto& element : s.shape_vector) {
        auto t = element->intersect(ray);
       /* if (t.cut){
            std::cout << "hit" << "\n";
        }*/
        if (t.t < closest_t.t){
            closest_t = t;
            closest_o = element;
        }
    }
    if (closest_o != nullptr){
        return shade(closest_o, ray, closest_t);
    }
}
//TODO shade implementieren
Color Renderer::shade(std::shared_ptr<Shape> sharedPtr, const Ray &ray, Hitpoint hitpoint) {

    return Color();
}


