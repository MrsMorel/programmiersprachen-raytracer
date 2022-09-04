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
            closest_t = hit;
            closest_o = element;
        }
    }
    if (closest_o != nullptr){
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

Color Renderer::shade(const Scene &s, std::shared_ptr<Shape> const& sharedPtr, const Ray &ray, const Hitpoint& hitpoint) {
    //point x = r(t) , t=distance into ray equation
    //evaluate illumination equation
    //generate new rays if reflection, refraction or shadows

    //ambient
    Color ka_ambient = calc_ambient(s, sharedPtr, hitpoint);
    // calc diffuse
    //Color kd_diffuse = calc_diffuse(s, sharedPtr, hitpoint);
    Color kd_diffuse{0.0f,0.0f,0.0f};
    Color ks_specular{0.0f,0.0f,0.0f};
    for (auto const &light: s.light_vector) {
        bool block = false; //normal muss in intersect an hitpoint gegeben werden!
        auto light_hit = Ray{hitpoint.point + (hitpoint.normal * 0.0001f), glm::normalize(light->pos - hitpoint.point)};
        //light origin negativ?
        //auto i = light_hit.direction;
        //auto r = i - 2 * glm::dot(i, hitpoint.normal) * hitpoint.normal;
        //auto v = hitpoint.direction;
        //auto r_dot_v = glm::clamp(glm::dot(r,v), 0.0f, 1.0f);
        //auto n = hitpoint.normal;
        for (auto const &sh: s.shape_vector) {
            if (sh->intersect(light_hit).cut) {
                block = true;
                break;
            }
        }
        if (!block){
            //auto l = light->color * light->brightness;
            glm::vec3 n = hitpoint.normal;
            glm::vec3 i = light_hit.direction;
            float dot_n_i = glm::clamp(glm::dot(n, i), 0.0f, 1.0f);
            kd_diffuse += (light->color * light->brightness * sharedPtr->material()->kd * dot_n_i);
            //ks_specular += l * sharedPtr->material()->ks * std::pow(r_dot_v, sharedPtr->material()->m_);
        }
    }
    return (ka_ambient + kd_diffuse + ks_specular);
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








