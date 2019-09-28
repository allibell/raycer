#include "raycer/materials/MatteMaterial.h"
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

Colord MatteMaterial::shade(const Raycer* raycer, const Rayd& ray, const HitPoint& hitPoint, State& state) const {
  auto texColor = diffuseTexture() ? diffuseTexture()->evaluate(ray, hitPoint) : Colord::black();

  Lambertian ambientBRDF(texColor, ambientCoefficient());
  Lambertian diffuseBRDF(texColor, diffuseCoefficient());

  // for diffuse BRDFs the in and out vectors are irrelevant, so let's not calculate them
  auto color = ambientBRDF.reflectance(hitPoint, Vector3d::null()) * raycer->scene()->ambient();

  for (const auto& light : raycer->scene()->lights()) {
    Vector3d in = light->direction(hitPoint.point());

    if (raycer->scene()->intersects(Rayd(hitPoint.point(), in).epsilonShifted(), state)) {
      state.shadowHit(this, "MatteMaterial");
    } else {
      state.shadowMiss(this, "MatteMaterial");
      double normalDotIn = hitPoint.normal() * in;
      if (normalDotIn > 0.0)
        color += diffuseBRDF(hitPoint, Vector3d::null(), Vector3d::null()) * light->radiance() * normalDotIn;
    }
  }

  return color;
}
