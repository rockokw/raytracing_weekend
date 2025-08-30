#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3 {
 public:
  double e_[3];

  Vec3() : e_{0, 0, 0} {}

  Vec3(double e0, double e1, double e2) : e_{e0, e1, e2} {}

  double x() const { return e_[0]; }
  double y() const { return e_[1]; }
  double z() const { return e_[2]; }

  Vec3 operator-() const { return Vec3{-e_[0], -e_[1], -e_[2]}; }
  double operator[](int i) const { return e_[i]; }
  double &operator[](int i) { return e_[i]; }

  Vec3 &operator+=(const Vec3 &v) {
    e_[0] += v.e_[0];
    e_[1] += v.e_[1];
    e_[2] += v.e_[2];
    return *this;
  }

  Vec3 &operator*=(double t) {
    e_[0] *= t;
    e_[1] *= t;
    e_[2] *= t;
    return *this;
  }

  Vec3 &operator/=(double t) { return *this *= 1 / t; }

  double length() const { return std::sqrt(length_squared()); }

  double length_squared() const {
    return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
  }
};

using Point3 = Vec3;

/* Vector Utility Functions */

inline std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
  return out << v.e_[0] << ' ' << v.e_[1] << ' ' << v.e_[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e_[0] + v.e_[0], u.e_[1] + v.e_[1], u.e_[2] + v.e_[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e_[0] - v.e_[0], u.e_[1] - v.e_[1], u.e_[2] - v.e_[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e_[0] * v.e_[0], u.e_[1] * v.e_[1], u.e_[2] * v.e_[2]);
}

inline Vec3 operator*(double t, const Vec3 &u) {
  return Vec3(t * u.e_[0], t * u.e_[1], t * u.e_[2]);
}

inline Vec3 operator*(const Vec3 &u, double t) { return t * u; }

inline Vec3 operator/(const Vec3 &u, double t) { return (1 / t) * u; }

inline double Dot(const Vec3 &u, const Vec3 &v) {
  return u.e_[0] * v.e_[0] + u.e_[1] * v.e_[1] + u.e_[2] * v.e_[2];
}

inline Vec3 Cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e_[1] * v.e_[2] - u.e_[2] * v.e_[1],
              u.e_[2] * v.e_[0] - u.e_[0] * v.e_[2],
              u.e_[0] * v.e_[1] - u.e_[1] * v.e_[0]);
}

inline Vec3 UnitVector(const Vec3 &u) { return u / u.length(); }

#endif
