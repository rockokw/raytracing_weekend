#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

using Color = Vec3;

void WriteColor(std::ostream &out, const Color &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Scale [0, 1] component values to the byte range [0, 255]
  int rbyte = static_cast<int>(255.999 * r);
  int gbyte = static_cast<int>(255.999 * g);
  int bbyte = static_cast<int>(255.999 * b);

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
