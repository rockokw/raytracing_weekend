#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

using std::max;

class Camera {
 public:
  double aspect_ratio = 1.0;  // Ratio of image width over height

  int image_width = 100;  // Rendered image width in pixel count

  void Render(const Hittable& world) {
    Initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height_ << "\n255\n";

    for (int row = 0; row < image_height_; ++row) {
      std::clog << "\rScanlines remaining: " << (image_height_ - row) << ' '
                << std::flush;
      for (int col = 0; col < image_width; ++col) {
        auto pixel_center =
            pixel00_loc_ + (col * pixel_delta_u_) + (row * pixel_delta_v_);
        auto ray_direction = pixel_center - center_;
        Ray r(center_, ray_direction);

        Color pixel_color = RayColor(r, world);
        WriteColor(std::cout, pixel_color);
      }
    }
    std::clog << "\rDone.                 \n";
  }

 private:
  int image_height_;  // Rendered image height in pixel count

  Point3 center_;  // Camera center

  Point3 pixel00_loc_;  // Location of pixel 0, 0

  Vec3 pixel_delta_u_;  // Offset of pixel to the right

  Vec3 pixel_delta_v_;  // Offset of pixel below

  void Initialize() {
    // Determine image height based on aspect ratio, with a min of 1.
    image_height_ = max(1, static_cast<int>(image_width / aspect_ratio));

    center_ = Point3(0, 0, 0);

    // Viewport dimensions
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height_);

    // Calculate horizontal and vertical viewport vectors.
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);

    pixel_delta_u_ = viewport_u / image_width;
    pixel_delta_v_ = viewport_v / image_height_;

    // Calculate viewport coordinates.
    auto viewport_upper_left =
        center_ - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc_ = viewport_upper_left;
  }

  Color RayColor(const Ray& r, const Hittable& world) const {
    HitRecord rec;
    if (world.Hit(r, Interval(0, infinity), rec)) {
      return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vec3 unit_direction = UnitVector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);

    const Color kWhite{1.0, 1.0, 1.0};
    const Color kBlue{0.5, 0.7, 1.0};
    return (1 - a) * kWhite + a * kBlue;
  }
};

#endif
