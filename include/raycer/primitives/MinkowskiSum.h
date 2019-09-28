#pragma once

#include "raycer/primitives/ConvexOperation.h"

namespace raycer {
  class MinkowskiSum : public ConvexOperation {
  public:
    virtual Vector3d farthestPoint(const Vector3d& direction) const;

  protected:
    virtual BoundingBoxd calculateBoundingBox() const;
  };
}
