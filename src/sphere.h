#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "rtweekend.h"

class Sphere : public Hittable {
 public:
  Sphere(const Point3& center, double radius)
      : center_(center), radius_(std::fmax(0, radius)) {}

  bool Hit(const Ray& r, double ray_tmin, double ray_tmax,
           HitRecord& rec) const override {
    Vec3 oc = center_ - r.origin();
    auto a = r.direction().LengthSquared();
    auto h = Dot(r.direction(), oc);
    auto c = oc.LengthSquared() - radius_ * radius_;

    auto discriminant = (h * h) - (a * c);
    if (discriminant < 0) {
      return false;
    }

    auto sqrtd = std::sqrt(discriminant);

    // Find nearest root that lies in the acceptable range of t.
    auto root = (h - sqrtd) / a;
    if (root <= ray_tmin or ray_tmax <= root) {
      root = (h + sqrtd) / a;
      if (root <= ray_tmin or ray_tmax <= root) {
        return false;
      }
    }

    rec.t = root;
    rec.p = r.At(rec.t);
    rec.normal = (rec.p - center_) / radius_;
    Vec3 outward_normal = (rec.p - center_) / radius_;
    rec.SetFaceNormal(r, outward_normal);

    return true;
  }

 private:
  Point3 center_;

  double radius_;
};

#endif