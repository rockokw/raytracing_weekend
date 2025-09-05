#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using Color = Vec3;

void WriteColor(std::ostream &out, const Color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Scale [0, 1] component values to the byte range [0, 255]
  static const Interval intensity(0.000, 0.999);
  int rbyte = static_cast<int>(256 * intensity.Clamp(r));
  int gbyte = static_cast<int>(256 * intensity.Clamp(g));
  int bbyte = static_cast<int>(256 * intensity.Clamp(b));

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
