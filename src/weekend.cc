#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"

int main() {
  /* World */
  HittableList world;
  world.Add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  /* Camera */
  Camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.Render(world);

  return 0;
}
