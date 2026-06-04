#pragma once
#include "vec3.h"

class Ray {
private:
  const Vec3 origin;
  const Vec3 direction;

public:
  Ray(const point &origin, const Vec3 &direction)
      : origin(origin), direction(direction) {}

  point at(double t) const { return origin + direction * t; }

  const Vec3 getOrigin() const { return origin; }

  const Vec3 getDirection() const { return direction; }
};
