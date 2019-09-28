#pragma once

#include "core/Color.h"
#include "core/math/Vector.h"
#include "core/math/Ray.h"

#include "raycer/Object.h"

class HitPoint;

namespace raycer {
  class Raycer;
  class State;

  class Material : public Object {
  public:
    virtual ~Material() {}

    virtual Colord shade(const Raycer* raycer, const Rayd& ray, const HitPoint& hitPoint, State& state) const = 0;
  };
}
