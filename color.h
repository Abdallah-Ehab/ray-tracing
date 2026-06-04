#pragma once

#include "vec3.h"

using color = Vec3;

// maps [0, 1] -> [0, 255]
Vec3 getColor(const Vec3 &v) {
  double r = 255.999 * v.x();
  double g = 255.999 * v.y();
  double b = 255.999 * v.z();

  return Vec3(r, g, b);
}
