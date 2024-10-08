#include "raycer/State.h"
#include "raycer/primitives/Sphere.h"
#include "core/math/Ray.h"
#include "core/math/HitPointInterval.h"
#include <cmath>

using namespace std;
using namespace raycer;

const Primitive* Sphere::intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const {
  const Vector3d& o = ray.origin() - m_origin, d = ray.direction();
  
  double od = o * d, dd = d * d;
  double discriminant = od * od - dd * (o * o - m_radius * m_radius);
  
  if (discriminant < 0) {
    state.miss(this, "Sphere, ray miss");
    return nullptr;
  } else if (discriminant > 0) {
    double discriminantRoot = sqrt(discriminant);
    double t1 = (-od - discriminantRoot) / dd;
    double t2 = (-od + discriminantRoot) / dd;
    
    Vector3d hitPoint1 = ray.at(t1),
             hitPoint2 = ray.at(t2);
    
    hitPoints.add(
      HitPoint(this, t1, hitPoint1, (hitPoint1 - m_origin) / m_radius),
      HitPoint(this, t2, hitPoint2, (hitPoint2 - m_origin) / m_radius)
    );
    
    if (t1 <= 0 && t2 <= 0) {
      state.miss(this, "Sphere, behind ray");
      return nullptr;
    } else {
      state.hit(this, "Sphere");
      return this;
    }
  }
  state.miss(this, "Sphere, ray miss");
  return nullptr;
}

bool Sphere::intersects(const Rayd& ray, State& state) const {
  const Vector3d& o = ray.origin() - m_origin, d = ray.direction();
  
  double od = o * d, dd = d * d;
  double discriminant = od * od - dd * (o * o - m_radius * m_radius);
  
  if (discriminant < 0) {
    state.shadowMiss(this, "Sphere, ray miss");
    return false;
  } else if (discriminant > 0) {
    double discriminantRoot = sqrt(discriminant);
    double t1 = (-od - discriminantRoot) / dd;
    double t2 = (-od + discriminantRoot) / dd;
    if (t1 <= 0 && t2 <= 0) {
      state.shadowMiss(this, "Sphere, behind ray");
      return false;
    }
    
    state.shadowHit(this, "Sphere");
    return true;
  }
  
  state.shadowMiss(this, "Sphere, ray miss");
  return false;
}

BoundingBoxd Sphere::calculateBoundingBox() const {
  Vector3d radius(m_radius, m_radius, m_radius);
  return BoundingBoxd(m_origin - radius, m_origin + radius);
}

Vector3d Sphere::farthestPoint(const Vector3d& direction) const {
  return m_origin + direction.normalized() * m_radius;
}
