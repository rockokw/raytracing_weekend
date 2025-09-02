#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>

#include "hittable.h"
#include "rtweekend.h"

class HittableList : public Hittable {
 public:
  std::vector<shared_ptr<Hittable>> objects_;

  HittableList() {}

  HittableList(shared_ptr<Hittable> object) { Add(object); }

  void Clear() { objects_.clear(); }

  void Add(shared_ptr<Hittable> object) { objects_.push_back(object); }

  bool Hit(const Ray& r, double ray_tmin, double ray_tmax,
           HitRecord& rec) const override {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_tmax;

    for (const auto& object : objects_) {
      if (object->Hit(r, ray_tmin, closest_so_far, temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }

    return hit_anything;
  }
};

#endif