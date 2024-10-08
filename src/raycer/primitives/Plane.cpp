#include "raycer/State.h"
#include "raycer/primitives/Plane.h"
#include "core/math/Ray.h"
#include "core/math/HitPointInterval.h"

using namespace raycer;

const Primitive* Plane::intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const {
  double t = calculateIntersectionDistance(ray);
  
  if (t > 0) {
    hitPoints.add(HitPoint(this, t, ray.at(t), m_normal));
    state.hit(this, "Plane");
    return this;
  } else {
    state.miss(this, "Plane, ray miss");
    return nullptr;
  }
}

bool Plane::intersects(const Rayd& ray, State& state) const {
  if (calculateIntersectionDistance(ray) > 0) {
    state.shadowHit(this, "Plane");
    return true;
  }
  
  state.shadowMiss(this, "Plane");
  return false;
}

double Plane::calculateIntersectionDistance(const Rayd& ray) const {
  const Vector3d& o = ray.origin(), d = ray.direction();
  
  double angle = m_normal * d;
  if (angle == 0)
    return false;
  
  return -(m_normal * o + m_distance) / angle;
}

BoundingBoxd Plane::calculateBoundingBox() const {
  return BoundingBoxd::infinity();
}
