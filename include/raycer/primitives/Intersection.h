#pragma once

#include "raycer/primitives/Composite.h"

namespace raycer {
  class Intersection : public Composite {
  public:
    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const;
    virtual bool intersects(const Rayd& ray, State& state) const;

  protected:
    virtual BoundingBoxd calculateBoundingBox() const;
  };
}
