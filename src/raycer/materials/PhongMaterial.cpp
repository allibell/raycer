#include "raycer/materials/PhongMaterial.h"
#include "raycer/State.h"
#include "raycer/Raycer.h"
#include "core/math/HitPoint.h"
#include "raycer/primitives/Scene.h"
#include "raycer/lights/Light.h"
#include "core/math/Ray.h"
#include "raycer/textures/Texture.h"

#include <algorithm>

using namespace std;
using namespace raycer;

Colord PhongMaterial::shade(const Raycer* raycer, const Rayd& ray, const HitPoint& hitPoint, State& state) const {
  auto texColor = diffuseTexture() ? diffuseTexture()->evaluate(ray, hitPoint) : Colord::black();

  Lambertian ambientBRDF(texColor, ambientCoefficient());
  Lambertian diffuseBRDF(texColor, diffuseCoefficient());

  Vector3d out = -ray.direction();
  auto color = ambientBRDF.reflectance(hitPoint, out) * raycer->scene()->ambient();

  for (const auto& light : raycer->scene()->lights()) {
    Vector3d in = light->direction(hitPoint.point());

    if (raycer->scene()->intersects(Rayd(hitPoint.point(), in).epsilonShifted(), state)) {
      state.shadowHit(this, "PhongMaterial");
    } else {
      state.shadowMiss(this, "PhongMaterial");
      double normalDotIn = hitPoint.normal() * in;
      if (normalDotIn > 0.0) {
        color += (
          diffuseBRDF(hitPoint, out, in)
        + m_specularBRDF(hitPoint, out, in)
        ) * light->radiance() * normalDotIn;
      }
    }
  }

  return color;
}
