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

void Renderer::render(const Scene &s, const Camera &c) {
    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            Pixel p(x,y);
            float dist = (width_/2.0f) /std::tan(c.fov_x * M_PI / 360.0f);
            glm::vec3 direction = {x-(width_ / 2.0f), y - (height_ / 2.0f), -dist};
            Ray ray{s.camera.position, glm::normalize(direction)};
            // TODO render fertigstellen
            
            p.color = trace(ray, s);
            write(p);

        }
    }
    ppm_.save(filename_);
}
//todo durch kamera generierten strahl mit scene schneiden, hitpoint über lichtquellen beleuchten

Color Renderer::trace(const Ray &ray, const Scene &s) {
    std::shared_ptr<Shape> closest_o;
    Hitpoint closest_t;
    Color background_color{0.0f,0.0f,0.0f};
    for (const auto& element : s.shape_vector) {
        auto hit = element->intersect(ray);
        float distance = glm::distance(s.camera.position, hit.intersection);
       /* if (hit.cut){
            std::cout << "hit" << "\n";
        }*/
        if (hit.t < closest_t.t){
            closest_t = hit;
            closest_o = element;
        }
    }
    if (closest_o != nullptr){
        return shade(s, closest_o, ray, closest_t);
    } else {
        return background_color;
    }
}
//TODO shade implementieren

Color Renderer::shade(const Scene &s, std::shared_ptr<Shape> const& sharedPtr, const Ray &ray, Hitpoint hitpoint) {
    //point x = r(t) , t=distance into ray equation
    //evaluate illumination equation
    //generate new rays if reflection, refraction or shadows
    //ambient
    Color ka = sharedPtr->material()->ka;
    Color ambient = s.ambient.color;
    Color calc_ambient = ka * s.ambient.color;
    Color shading = calc_ambient;
    return shading;}
/*
Color Renderer::calc_diffuse(const Scene &s, const std::shared_ptr<Shape> &sharedPtr, const Hitpoint& hitpoint) {
    //diffuse
    Color calc_diffuse;
    Hitpoint hit_help;
    for (auto light : s.light_vector) {
        bool block = false;
        Ray ray_help{glm::normalize(hitpoint.intersection), glm::normalize(light->pos - hitpoint.intersection)};
        for (auto shape: s.shape_vector) {
            hit_help = shape->intersect(ray_help);
            //punktlicht
        }
    }
    return Color();
}*/






