#include "raycer/State.h"
#include "raycer/primitives/Torus.h"
#include "core/math/Ray.h"
#include "core/math/HitPointInterval.h"
#include "core/math/Quartic.h"
#include <cmath>

using namespace std;
using namespace raycer;

const Primitive* Torus::intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const {
  if (!boundingBoxIntersects(ray)) {
    state.miss(this, "Torus, bounding box miss");
    return nullptr;
  }
  
  Vector3d origin = ray.origin();
  Vector3d direction = ray.direction();
  
  double dd = direction * direction;
  double oorr = origin * origin - m_sweptRadius * m_sweptRadius - m_tubeRadius * m_tubeRadius;
  double od = origin * direction;
  double fourRR = 4.0 * m_sweptRadius * m_sweptRadius;
  
  Quartic<double> quartic(
    dd * dd,
    4.0 * dd * od,
    2.0 * dd * oorr + 4.0 * od * od + fourRR * direction.y() * direction.y(),
    4.0 * od * oorr + 2.0 * fourRR * origin.y() * direction.y(),
    oorr * oorr - fourRR * (m_tubeRadius * m_tubeRadius - origin.y() * origin.y())
  );
  
  vector<double> results = quartic.sortedResult();
  
  if (results.size() == 2 || results.size() == 4) {
    Vector3d hitPoint1 = ray.at(results[0]),
             hitPoint2 = ray.at(results[1]);
    hitPoints.add(
      HitPoint(this, results[0], hitPoint1, computeNormal(hitPoint1)),
      HitPoint(this, results[1], hitPoint2, computeNormal(hitPoint2))
    );
  }
  
  if (results.size() == 4) {
    Vector3d hitPoint1 = ray.at(results[2]),
             hitPoint2 = ray.at(results[3]);
    hitPoints.add(
      HitPoint(this, results[2], hitPoint1, computeNormal(hitPoint1)),
      HitPoint(this, results[3], hitPoint2, computeNormal(hitPoint2))
    );
  }
  
  if (hitPoints.empty()) {
    state.miss(this, "Torus, ray miss");
    return nullptr;
  }

  auto hitPoint = hitPoints.minWithPositiveDistance();
  if (hitPoint.isUndefined()) {
    state.miss(this, "Torus, behind Ray");
    return nullptr;
  } else {
    state.hit(this, "Torus");
    return this;
  }
}

BoundingBoxd Torus::calculateBoundingBox() const {
  Vector3d corner(m_sweptRadius + m_tubeRadius, m_tubeRadius, m_sweptRadius + m_tubeRadius);
  return BoundingBoxd(-corner, corner);
}

Vector3d Torus::computeNormal(const Vector3d& p) const {
  double paramSquared = m_sweptRadius * m_sweptRadius + m_tubeRadius * m_tubeRadius;
  double sumSquared = p * p;
  
  Vector3d result(
    4.0 * p.x() * (sumSquared - paramSquared),
    4.0 * p.y() * (sumSquared - paramSquared + 2.0 * m_sweptRadius * m_sweptRadius),
    4.0 * p.z() * (sumSquared - paramSquared)
  );
  
  return result.normalized();
}
