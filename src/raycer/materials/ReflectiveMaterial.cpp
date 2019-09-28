#include "raycer/materials/ReflectiveMaterial.h"
#include "raycer/State.h"
#include "raycer/Raycer.h"
#include "core/math/HitPoint.h"
#include "core/math/Ray.h"

using namespace raycer;

Colord ReflectiveMaterial::shade(const Raycer* raycer, const Rayd& ray, const HitPoint& hitPoint, State& state) const {
  auto color = PhongMaterial::shade(raycer, ray, hitPoint, state);

  Vector3d out = - ray.direction();
  Vector3d in;
  Colord refl = m_reflectiveBRDF.sample(hitPoint, out, in);
  Rayd reflected(hitPoint.point(), in);

  double normalDotIn = hitPoint.normal() * in;

  state.recordEvent(this, "ReflectiveMaterial: Tracing reflection");
  color += refl * raycer->rayColor(reflected.epsilonShifted(), state) * normalDotIn;

  return color;
}
