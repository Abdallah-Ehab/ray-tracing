#include "hittable.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

struct viewport {
  double width;
  double height;
};

class Camera {
private:
  double aspectRatio;
  double imageHeight;
  double imageWidth;
  Vec3 position;
  viewport vp;

public:
  void setAspectRatio(double aspectRatio) { this->aspectRatio = aspectRatio; }
  void setImageHeight(double imageHeight) { this->imageHeight = imageHeight; }
  void setImageWidth(double imageWidth) { this->imageWidth = imageWidth; }
  void setPosition(const Vec3 &position) { this->position = position; }

  const double getAspectRatio() const { return aspectRatio; }
  const double getImageHeight() const { return imageHeight; }
  const double getImageWidth() const { return imageWidth; }
  const Vec3 getPosition() const { return position; }
  void init() {
    double viewport_height = 2.0;
    double viewport_width =
        viewport_height * (static_cast<double>(imageWidth) / imageHeight);
    vp.width = viewport_width;
    vp.height = viewport_height;
  }

  Vec3 getRayColor(const Ray &ray, const HittableList &world) {
    hitRecord temprec;
    if (world.isHit(ray, 0.0001, std::numeric_limits<double>::infinity(),
                    temprec)) {
      Vec3 diffuseReflectionVector = generateRandomVectorFromHemisphere(ray);
      Ray diffuseReflectoinRay(temprec.p, diffuseReflectionVector);
      return Vec3(0.5, 0.5, 0.5) * getRayColor(diffuseReflectoinRay, world);
    }
    double t = 0.5 * (ray.getDirection().y() + 1.0);
    return Vec3(1.0, 1.0, 1.0) * (1.0 - t) + Vec3(0.5, 0.7, 1.0) * t;
  }

  Vec3 generateRandomVectorFromHemisphere(const Ray &ray) const {

    while (true) {
      auto normal = ray.getDirection();
      Vec3 randomVec = Vec3::random(-1, 1);
      if (randomVec.dot(normal) > 0.0) {
        return randomVec;
      }
    }
  }
  void render(HittableList &world) {
    init();
    double deltaU = vp.width / imageWidth;
    double deltaV = vp.height / imageHeight;
    Vec3 topLeftCorner =
        position - Vec3(0, 0, 1) - Vec3(vp.width / 2, vp.height / 2, 0);
    std::clog << "top left corner is" << topLeftCorner << std::endl
              << std::flush;
    for (int j = 0; j < imageHeight; j++) {
      for (int i = 0; i < imageWidth; i++) {

        Vec3 pixelPos =
            topLeftCorner + Vec3(i * deltaU, (imageHeight - 1 - j) * deltaV, 0);
        Ray ray(position, pixelPos - this->position);
        Vec3 color = getRayColor(ray, world);

        std::cout << static_cast<int>(255.999 * color.x()) << " "
                  << static_cast<int>(255.999 * color.y()) << " "
                  << static_cast<int>(255.999 * color.z()) << "\n";
      }
    }
  }
};
