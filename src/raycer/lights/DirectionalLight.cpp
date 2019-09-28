#include "raycer/lights/DirectionalLight.h"

using namespace raycer;

Vector3d DirectionalLight::direction(const Vector3d&) const {
  return direction();
}

Colord DirectionalLight::radiance() const {
  return color();
}
