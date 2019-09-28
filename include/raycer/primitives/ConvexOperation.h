#pragma once

#include "raycer/primitives/Composite.h"

namespace raycer {
  class ConvexOperation : public Composite {
  public:
    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const;
    virtual bool intersects(const Rayd& ray, State& state) const;

    virtual Vector3d farthestPoint(const Vector3d& direction) const = 0;
  };
}
