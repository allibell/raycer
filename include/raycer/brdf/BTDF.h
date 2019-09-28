#pragma once

#include "raycer/brdf/BRDF.h"
#include "core/math/Ray.h"

namespace raycer {
  class BTDF : BRDF {
  public:
    virtual bool totalInternalReflection(const Rayd& ray, const HitPoint& hitPoint) const = 0;
  };
}
