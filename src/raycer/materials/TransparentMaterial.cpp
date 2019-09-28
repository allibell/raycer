#include "raycer/materials/TransparentMaterial.h"
#include "raycer/State.h"
#include "raycer/Raycer.h"
#include "core/math/HitPoint.h"
#include "core/math/Ray.h"

#include <algorithm>

using namespace std;
using namespace raycer;

Colord TransparentMaterial::shade(const Raycer* raycer, const Rayd& ray, const HitPoint& hitPoint, State& state) const {
  Vector3d out = -ray.direction();
  Vector3d in;
  Colord reflectedColor = m_reflectiveBRDF.sample(hitPoint, out, in);
  Rayd reflected(hitPoint.point(), in);

  if (m_specularBTDF.totalInternalReflection(ray, hitPoint)) {
    return raycer->rayColor(reflected.epsilonShifted(), state);
  } else {
    auto color = PhongMaterial::shade(raycer, ray, hitPoint, state);

    Vector3d trans;
    Colord transmittedColor = m_specularBTDF.sample(hitPoint, out, trans);
    Rayd transmitted(hitPoint.point(), trans);

    state.recordEvent(this, "TransparentMaterial: Tracing reflection");
    color += reflectedColor * raycer->rayColor(reflected.epsilonShifted(), state) * fabs(hitPoint.normal() * in);

    state.recordEvent(this, "TransparentMaterial: Tracing transmission");
    color += transmittedColor * raycer->rayColor(transmitted.epsilonShifted(), state) * fabs(hitPoint.normal() * trans);

    return color;
  }
}
