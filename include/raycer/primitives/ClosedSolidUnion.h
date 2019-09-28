#pragma once

#include "raycer/primitives/Composite.h"

namespace raycer {
  class ClosedSolidUnion : public Composite {
  public:
    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const;
    virtual Vector3d farthestPoint(const Vector3d& direction) const;
  };
}
