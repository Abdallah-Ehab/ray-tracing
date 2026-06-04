#include "camera.h"

#include <iostream>
#include <memory>

int main() {
  Camera camera;
  camera.setAspectRatio(16.0 / 9.0);
  camera.setImageHeight(1080);
  camera.setImageWidth(static_cast<int>(camera.getImageHeight() * camera.getAspectRatio()));
  camera.setPosition(Vec3(0, 0, 1));

  std::cout << "P3\n"
            << camera.getImageWidth()
            << " "
            << camera.getImageHeight()
            << "\n255\n";

  HittableList world;
  world.add(std::make_shared<sphere>(point(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point(0, -100.5, -1), 100));
  camera.render(world);

  std::clog << "\rDone.                 \n";
}
