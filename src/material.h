#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class Material {
 public:
  virtual ~Material() = default;

  virtual bool Scatter([[maybe_unused]] const Ray& r_in,
                       [[maybe_unused]] const HitRecord& rec,
                       [[maybe_unused]] Color& attentuation,
                       [[maybe_unused]] Ray& scattered) const {
    return false;
  }
};

class Lambertian : public Material {
 public:
  Lambertian(const Color& albedo) : albedo_(albedo) {}

  bool Scatter([[maybe_unused]] const Ray& r_in, const HitRecord& rec,
               Color& attentuation, Ray& scattered) const override {
    auto scatter_direction = rec.normal + RandomUnitVector();

    // Catch degenerate scatter directions.
    if (scatter_direction.NearZero()) scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attentuation = albedo_;
    return true;
  }

 private:
  Color albedo_;
};

class Metal : public Material {
 public:
  Metal(const Color& albedo, double fuzz)
      : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1) {}

  bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenutation,
               Ray& scattered) const override {
    Vec3 reflected = Reflect(r_in.direction(), rec.normal);
    reflected = UnitVector(reflected) + (fuzz_ * RandomUnitVector());
    scattered = Ray(rec.p, reflected);
    attenutation = albedo_;
    return (Dot(scattered.direction(), rec.normal) > 0);
  }

 private:
  Color albedo_;

  double fuzz_;
};

#endif
