// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "scene.hpp"
#include <string>
#include <glm/glm.hpp>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  void render();
  void render(Scene const& s, Camera const& c);
  void write(Pixel const& p);
  Color trace(Ray const& ray, Scene const& s);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }
  inline unsigned get_width() const {
        return width_;
  }
  inline unsigned get_height() const {
        return height_;
  }
  inline std::string get_filename() const {
        return filename_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;

  Color shade(const Scene &scene, std::shared_ptr<Shape> const& sharedPtr, const Ray &ray, Hitpoint hitpoint);
  Color calc_diffuse(const Scene &s, std::shared_ptr<Shape> const& sharedPtr,const Hitpoint& hitpoint);
};

#endif // #ifndef BUW_RENDERER_HPP
