#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"

using std::max;

Color RayColor(const Ray& r, const Hittable& world) {
  HitRecord rec;
  if (world.Hit(r, Interval(0, infinity), rec)) {
    return 0.5 * (rec.normal + Color(1, 1, 1));
  }

  Vec3 unit_direction = UnitVector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);

  Color white{1.0, 1.0, 1.0};
  Color blue{0.5, 0.7, 1.0};
  return (1 - a) * white + a * blue;
}

int main() {
  /* Image */
  auto aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // Determine image height based on aspect ratio, with a min of 1.
  int image_height = max(1, static_cast<int>(image_width / aspect_ratio));

  /* World */
  HittableList world;
  world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  /* Camera */
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width =
      viewport_height * (static_cast<double>(image_width) / image_height);
  auto camera_center = Point3(0, 0, 0);

  // Calculate horizontal and vertical viewport vectors.
  auto viewport_u = Vec3(viewport_width, 0, 0);
  auto viewport_v = Vec3(0, -viewport_height, 0);

  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  // Calculate viewport coordinates.
  auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) -
                             viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc = viewport_upper_left;

  /* Render */
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int row = 0; row < image_height; ++row) {
    std::clog << "\rScanlines remaining: " << (image_height - row) << ' '
              << std::flush;
    for (int col = 0; col < image_width; ++col) {
      auto pixel_center =
          pixel00_loc + (col * pixel_delta_u) + (row * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      Ray r(camera_center, ray_direction);

      Color pixel_color = RayColor(r, world);
      WriteColor(std::cout, pixel_color);
    }
  }
  std::clog << "\rDone.                 \n";

  return 0;
}
