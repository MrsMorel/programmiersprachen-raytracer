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

    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            Pixel p(x,y);
                       // TODO render fertigstellen

            Ray ray = s.camera.c_ray(x , y , width_, height_);
            p.color = tonemap(trace(ray, s));
            write(p);

        }
    }
    ppm_.save(filename_);
}
//todo durch kamera generierten strahl mit scene schneiden, hitpoint über lichtquellen beleuchten

Color Renderer::trace(const Ray &ray, const Scene &s) {
    std::shared_ptr<Shape> closest_o = nullptr;
    Hitpoint closest_t;
    closest_t.t = INFINITY;
    for (const auto& element : s.shape_vector) {
        Hitpoint hit = element->intersect(ray);
        /*if (hit.cut){
            std::cout << "hit" << "\n";
        }*/
        if (hit.cut && hit.t < closest_t.t){
            closest_t = hit;
            closest_o = element;
        }
    }
    if (closest_o != nullptr){
        return shade(s, closest_o, ray, closest_t);
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
/*
    Color c_ambient = calc_ambient(s, sharedPtr, hitpoint);
    Color c_diffuse = calc_diffuse(s, sharedPtr, hitpoint);
    Color shading = c_ambient + c_diffuse;
    return shading;*/

    // other method
    Color kd_total;
    for (auto const& light : s.light_vector) {
        auto hitpoint_to_light =
                Ray{hitpoint.point, glm::normalize(light->pos - hitpoint.point)};
        auto n_dot_i = glm::clamp(
                glm::dot(hitpoint.normal, hitpoint_to_light.direction), 0.f, 1.f);
        bool shadow = false;
        for (auto const& sh : s.shape_vector) {
            if (sharedPtr == sh)
                continue;
            if (sh->intersect(hitpoint_to_light).cut)
                shadow = true;
        }
        if (!shadow)
            kd_total += light->color * light->brightness * sharedPtr->material()->kd * n_dot_i;
    }

    return sharedPtr->material()->ka * s.ambient.color  + kd_total;

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
Color Renderer::calc_diffuse( Scene const& scene, std::shared_ptr<Shape> const& shape,Hitpoint const& hit){
    Color diffused_clr{0.0f,0.0f,0.0f};
    std::vector<Color> result;

    for(auto light : scene.light_vector){
        bool obstacle = false;
        Hitpoint light_hit;

        glm::vec3 vec_lights{light->pos - hit.point};
        Ray ray_lights{hit.point + 0.1f * hit.normal,glm::normalize(vec_lights)}; //checks if obstacle is between Light and intersection

        for(auto i : scene.shape_vector){
            light_hit = i->intersect(ray_lights);
            // erstmal unwichtig  std::cout << i->intersect(ray_lights).intersect_pt_.x << " " << i->intersect(ray_lights).intersect_pt_.y << " " << i->intersect(ray_lights).intersect_pt_.z << std::endl;
            if(light_hit.cut){
                obstacle = true;
            }
        }

        if(obstacle){
            //std::cout << "we use the obstacle, it is true" << std::endl;
            Color ip{light->color * light->brightness};
            Color kd = shape->material()->kd;
            float cross_prod = -(glm::dot(hit.normal,glm::normalize(vec_lights)));
            //std::cout << cross_prod << std::endl;
            cross_prod = std::max(cross_prod, 0.0f);
            //std::cout << cross_prod << std::endl;
            //std::cout << kd;
            //std::cout << ip;
            //printVec(vec_lights);
            //printVec(hit.normal_);
            //std::cout << ((ip*kd)*cross_prod) << std::endl;
            result.push_back({(ip*kd)*cross_prod});
            //std::cout << std::endl;
        }
    }
    //std::cout << "the Vec has this many elements: " << result.size() << std::endl;
    //std::cout << "first element: " << result[0] << std::endl;
    for(auto clr : result){
        //Color clamp_clr = clamping(clr);
        //diffused_clr += clamp_clr;
    }
    //std::cout << diffused_clr << std::endl;
    //std::cout << "" << std::endl;
    return diffused_clr;
}


/*
Color Renderer::calculateSpecular(std::shared_ptr<Shape> const& shape, Scene const& scene, HitPoint const& hit){
    Color spec_clr{0.0f,0.0f,0.0f};
    std::vector<Color> calc_clrs;

    for(auto light : scene.light_vec){
        bool obstacle = false;
        HitPoint light_hit;

        glm::vec3 vec_lights{light->pos_ - hit.intersect_pt_};
        Ray ray_lights{hit.intersect_pt_ + 0.1f * hit.normal_,glm::normalize(vec_lights)}; //checks if obstacle is between Light and intersection

        for(auto i : scene.shape_vec){
            light_hit = i->intersect(ray_lights);
            if(light_hit.intersection_){
                obstacle = true;
            }
        }

        if(obstacle){
            float m = shape->getMat()->m_;
            glm::vec3 r = 2.0f*glm::dot(hit.normal_,glm::normalize(vec_lights))*hit.normal_-glm::normalize(vec_lights); //glm::dot -> Skalarprodukt
            //printVec(r);
            glm::vec3 v = glm::normalize(scene.camera_.pos_ - hit.intersect_pt_);
            //printVec(v);
            //std::cout << std::endl;
            float cross_prod = glm::dot(r,v);
            cross_prod = std::max(cross_prod, 0.0f);
            if(cross_prod < 0){
                cross_prod = -cross_prod;}
            Color ks = shape->getMat()->ks_;
            Color ip{light->color_*light->brightness_};
            float cos = pow(cross_prod,m);
            float m_2 = (m+2)/(2*M_PI);
            calc_clrs.push_back({((ks*ip)*cos)*m_2});
        }

    }

    //std::cout << calc_clrs.size();
    for(auto clr : calc_clrs){
        Color clamp_clr = {clamping(clr)};
        spec_clr += clamp_clr;
    }
    return spec_clr;
}*/







