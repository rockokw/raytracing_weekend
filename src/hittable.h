#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

struct HitRecord {
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;

  void SetFaceNormal(const Ray& r, const Vec3& outward_normal) {
    // Sets the hit record normal vector.
    // NOTE: The parameter `outward_normal` is assumed to have unit length.
    front_face = Dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
 public:
  virtual ~Hittable() = default;

  virtual bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

#endif
