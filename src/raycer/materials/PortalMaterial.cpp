#include "raycer/materials/PortalMaterial.h"
#include "raycer/Raycer.h"
#include "core/math/HitPoint.h"

using namespace std;
using namespace raycer;

void PortalMaterial::setMatrix(const Matrix4d& matrix) {
  m_originMatrix = matrix.inverted();
  m_directionMatrix = Matrix3d(m_originMatrix);
}

Colord PortalMaterial::shade(const Raycer* raycer, const Rayd& ray, const HitPoint& hitPoint, State& state) const {
  return raycer->rayColor(transformedRay(ray.from(hitPoint.point()).epsilonShifted()), state) * m_filterColor;
}
