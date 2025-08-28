#include <iostream>

#include "color.h"

int main() {
  /* Image */
  int image_width = 256;
  int image_height = 256;

  /* Render */
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int row = 0; row < image_height; ++row) {
    std::clog << "\rScanlines remaining: " << (image_height - row) << ' '
              << std::flush;
    for (int col = 0; col < image_width; ++col) {
      auto pixel_color =
          Color(static_cast<double>(col) / (image_width - 1),
                static_cast<double>(row) / (image_height - 1), 0.0);

      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\rScanlines remaining: 0" << std::endl;

  return 0;
}
