#include "ray.h"
#include "vec3.h"
#include <memory>
#include <vector>

// TODO: complete this interface and make it so that we can have multiple
// hittable objects in the scene

struct hitRecord {
  double t;
  Vec3 normal;
  bool frontFace;
  point p;
  inline void setFaceNormal(const Ray &ray, const Vec3 &outwardNormal) {
    frontFace = ray.getDirection().dot(outwardNormal) < 0;
    normal = frontFace ? outwardNormal : outwardNormal * -1;
  }
};

class Hittable {

public:
  virtual ~Hittable() = default;
  Hittable() = default;
  virtual bool isHit(const Ray &ray, double tmin, double tmax,
                     hitRecord &rec) const = 0;
};

class HittableList : public Hittable {

private:
  std::vector<std::shared_ptr<Hittable>> objects;

public:
  void add(std::shared_ptr<Hittable> surface) { objects.push_back(surface); }

  bool isHit(const Ray &ray, double tmin, double tmax,
             hitRecord &rec) const override {
    bool isHit = false;
    double closestSoFar = tmax;
    for (auto object : objects) {
      if (object->isHit(ray, tmin, closestSoFar, rec)) {
        isHit = true;
        closestSoFar = rec.t;
      }
    }
    return isHit;
  }
};

class sphere : public Hittable {
private:
  Vec3 center;
  double r;

public:
  sphere(Vec3 center, double r) : center(center), r(r) {}
  bool isHit(const Ray &ray, double tmin, double tmax,
             hitRecord &rec) const override {
    Vec3 direction = ray.getDirection();
    point start = ray.getOrigin();
    point oc = center - start;
    auto a = direction.dot(direction);
    auto h = direction.dot(oc);
    auto c = (oc).dot(oc) - r * r;
    auto discriminant = h * h - a * c;
    if (discriminant < 0)
      return false;

    double sqrtd = std::sqrt(discriminant);
    double root = (h - sqrtd) / a;
    if (root < tmin || root > tmax) {
      root = (h + sqrtd) / a;
      if (root < tmin || root > tmax)
        return false;
    }
    rec.t = root;
    rec.p = ray.at(rec.t);
    Vec3 outwardNormal = (center - rec.p) * (1.0 / r);
    rec.normal = outwardNormal;
    // TODO: generate random vectors from the point of collision at t to any
    // random direction in the hemisphere of the normal vector. This will be
    // used for diffuse reflection
    rec.setFaceNormal(ray, outwardNormal);
    return true;
  }
};
