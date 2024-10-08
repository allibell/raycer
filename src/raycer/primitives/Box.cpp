#include "raycer/State.h"
#include "raycer/primitives/Box.h"
#include "core/math/Ray.h"
#include "core/math/HitPointInterval.h"
#include <cmath>

using namespace std;
using namespace raycer;

const Primitive* Box::intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const {
  int parallel = 0;
  bool found = false;
  Vector3d d = m_center - ray.origin();
  double t1 = 0, t2 = 0;
  Vector3d normal1, normal2;

  for (int i = 0; i < 3; ++i) {
    if (fabs(ray.direction()[i]) < 0.0001) {
      parallel |= 1 << i;
    } else {
      double dir = (ray.direction()[i] > 0.0) ? 1.0 : -1.0;
      double es = (ray.direction()[i] > 0.0) ? m_edge[i] : -m_edge[i];
      double invDi = 1.0 / ray.direction()[i];

      if (!found) {
        normal1[i] = -dir;
        normal2[i] = dir;
        t1 = (d[i] - es) * invDi;
        t2 = (d[i] + es) * invDi;
        found = true;
      } else {
        double s = (d[i] - es) * invDi;
        if (s > t1) {
          normal1 = Vector3d();
          normal1[i] = -dir;
          t1 = s;
        }
        s = (d[i] + es) * invDi;
        if (s < t2) {
          normal2 = Vector3d();
          normal2[i] = dir;
          t2 = s;
        }
        if (t1 > t2) {
          state.miss(this, "Box, ray miss");
          return nullptr;
        }
      }
    }
  }

  if (parallel)
    for (int i = 0; i < 3; ++i)
      if (parallel & (1 << i))
        if (fabs(d[i] - t1 * ray.direction()[i]) > m_edge[i] || fabs(d[i] - t2 * ray.direction()[i]) > m_edge[i]) {
          state.miss(this, "Box, ray parallel");
          return nullptr;
        }

  hitPoints.add(
    HitPoint(this, t1, ray.at(t1), normal1),
    HitPoint(this, t2, ray.at(t2), normal2)
  );

  if (t1 < 0 && t2 < 0) {
    state.miss(this, "Box, behind ray");
    return nullptr;
  }

  state.hit(this, "Box");
  return this;
}

bool Box::intersects(const Rayd& ray, State&) const {
  return boundingBox().intersects(ray);
}

BoundingBoxd Box::calculateBoundingBox() const {
  return BoundingBoxd(m_center - m_edge, m_center + m_edge);
}

Vector3d Box::farthestPoint(const Vector3d& direction) const {
  return m_center + Vector3d(
    direction.x() < 0.0 ? -m_edge.x() : m_edge.x(),
    direction.y() < 0.0 ? -m_edge.y() : m_edge.y(),
    direction.z() < 0.0 ? -m_edge.z() : m_edge.z()
  );
}
