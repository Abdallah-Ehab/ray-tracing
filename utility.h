#include <cstdlib>

class utitility {
public:

  static const double random() { return rand() / (RAND_MAX + 1.0); }
  static const double random(double min, double max) {
    return min + (max - min) * random();
  }
};
