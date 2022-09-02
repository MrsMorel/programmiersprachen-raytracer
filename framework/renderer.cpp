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
/*
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
*/
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
/*
void Renderer::render(const Scene &s) {
    for (unsigned y = 0; y < s.rend.height; ++y) {
        for (unsigned x = 0; x < s.rend.width; ++x) {
            Pixel p{x,y};
            for (const auto& element : s.shape_vector) {
                Ray ray = s.camera.c_ray(x , y , s.rend.width, s.rend.height);
                std::cout << ray.direction.x << "\n";
                Hitpoint hit = element->intersect(ray);
                if (hit.cut) {
                    std::cout << "cut" << "\n";
                    p.color = {1.0f,0.0f,0.0f};
                }

            }
            write(p);
        }
    }
    ppm_.save(filename_);
}*/

void Renderer::render(const Scene &s) {
    for (unsigned y = 0; y < s.rend.height; ++y) {
        for (unsigned x = 0; x < s.rend.width; ++x) {
            Pixel p{x,y};
            Ray ray = s.camera.c_ray(x , y , s.rend.width, s.rend.height);
            p.color = tonemap(trace(ray, s));
            write(p);
        }
    }
    ppm_.save(filename_);
}
//todo durch kamera generierten strahl mit scene schneiden, hitpoint über lichtquellen beleuchten
//Algorithmus auf Folien
Color Renderer::trace(const Ray &ray, const Scene &s) {
    std::shared_ptr<Shape> closest_o = nullptr;
    Hitpoint closest_t;
    closest_t.t = INFINITY;
    for (const auto& element : s.shape_vector) {
        Hitpoint hit = element->intersect(ray);
        /*if (hit.cut){
            std::cout << "hit" << "\n";
        }*/
        if (hit.cut && (hit.t < closest_t.t)){
            std::cout << "hit" << "\n";

            closest_t = hit;
            closest_o = element;
        }
    }
    if (closest_o != nullptr){
        std::cout << "aaaaa" << "\n";

        Color shaded =  shade(s, closest_o, ray, closest_t);
        Color depth{closest_t.t/10.0f, closest_t.t /10.0f, closest_t.t/10.0f};
        Color position{std::abs(closest_t.point.x /200.0f),std::abs(closest_t.point.y /200.0f),std::abs(closest_t.point.z /200.0f)};
        Color normal = {std::abs(closest_t.normal.x), std::abs(closest_t.normal.y), std::abs(closest_t.normal.z)};
        return shaded;
    } else {
        return s.ambient.color;
    }
}
//TODO shade implementieren

Color Renderer::shade(const Scene &s, std::shared_ptr<Shape> const& sharedPtr, const Ray &ray, Hitpoint hitpoint) {
    //point x = r(t) , t=distance into ray equation
    //evaluate illumination equation
    //generate new rays if reflection, refraction or shadows

    //ambient
    Color ka_ambient = calc_ambient(s, sharedPtr, hitpoint);
    // calc diffuse
    //Color kd_diffuse = calc_diffuse(s, sharedPtr, hitpoint);
    Color kd_diffuse{0.0f,0.0f,0.0f};
    for (auto const &light: s.light_vector) {
        bool block = false; //normal muss in intersect an hitpoint gegeben werden!
        auto light_hit = Ray{hitpoint.point + hitpoint.normal * 0.001f, glm::normalize(light->pos - hitpoint.point)};
        for (auto const &sh: s.shape_vector) {
            if (sh->intersect(light_hit).cut) {
                block = true;
                std::cout << "block" << "\n";
                break;
            }
        }
        if (!block){
            float dot_l_n = std::max(glm::dot(hitpoint.normal, light_hit.direction), 0.0f);
            kd_diffuse += (light->color * light->brightness * sharedPtr->material()->kd * dot_l_n);
        }
    }
    return ka_ambient + kd_diffuse;
}


Color Renderer::tonemap(Color const& clr){
    Color color_help{ clr.r / (clr.r + 1.0f) , clr.g / (clr.g + 1.0f) , clr.b / (clr.b + 1.0f)};
    return color_help;
}

Color Renderer::calc_ambient(const Scene &s, const std::shared_ptr<Shape> &sharedPtr, const Hitpoint &hitpoint) {
    Color ka = sharedPtr->material()->ka;
    Color calc_ambient = ka * s.ambient.color;
    return calc_ambient ;
}
/*
Color Renderer::calc_diffuse( Scene const& scene, std::shared_ptr<Shape> const& shape,Hitpoint const& hit){
    Color c_diffuse{0.0f, 0.0f, 0.0f};
    Color sum;

    for(const auto& light : scene.light_vector){
        Hitpoint hit_light;
        bool block = false;
        Ray ray_of_light{hit.point + 0.1f * hit.normal, glm::normalize(light->pos - hit.point)};
        for(const auto& element : scene.shape_vector){
            hit_light = element->intersect(ray_of_light);
            if(hit_light.cut){
                block = true;
            }
        }
        if(!block){
            Color clr{light->color * light->brightness};
            Color kd = shape->material()->kd;
            float x = -(glm::dot(hit.normal, glm::normalize(light->pos - hit.point)));
            x = std::max(x, 0.0f); //clamp
            sum += (clr * kd) * x;
        }
    }
    return c_diffuse;
}*/










