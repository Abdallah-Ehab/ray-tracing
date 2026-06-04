#pragma once
#include "ostream"
#include "utility.h"
#include <math.h>

class Vec3 {
private:
  double p[3];

public:
  Vec3() : p{0, 0, 0} {}

  Vec3(double e0, double e1, double e2) : p{e0, e1, e2} {}

  inline double x() const { return p[0]; }
  inline double y() const { return p[1]; }
  inline double z() const { return p[2]; }

  const double mag() const {
    return std::sqrt(x() * x() + y() * y() + z() * z());
  }

  double distance() { return x() * x() + y() * y() + z() * z(); }

  const double dot(const Vec3 &v) const {
    return x() * v.x() + y() * v.y() + z() * v.z();
  }

  static const Vec3 random() {
    return Vec3(utitility::random(), utitility::random(), utitility::random());
  }
  static const Vec3 random(double min, double max) {
    return Vec3(utitility::random(min, max), utitility::random(min, max),
                utitility::random(min, max));
  }
};

std::ostream &operator<<(std::ostream &os, const Vec3 &p) {
  os << "(" << p.x() << ", " << p.y() << ")";
  return os; // 3. Return the stream to allow chaining
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vec3 operator*(const Vec3 &u, double t) {
  return Vec3(u.x() * t, u.y() * t, u.z() * t);
}

using point = Vec3;
