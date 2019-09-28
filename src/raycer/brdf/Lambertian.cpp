#include "raycer/brdf/Lambertian.h"
#include "core/math/Constants.h"

using namespace raycer;

Colord Lambertian::calculate(const HitPoint&, const Vector3d&, const Vector3d&) const {
  return diffuseColor() * reflectionCoefficient() * invPI;
}

Colord Lambertian::reflectance(const HitPoint&, const Vector3d&) const {
  return diffuseColor() * reflectionCoefficient();
}
