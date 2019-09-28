#pragma once

#include "core/Color.h"
#include "core/math/Ray.h"

#include "raycer/Object.h"

class HitPoint;

namespace raycer {
  template<class T>
  class Texture : public Object {
  public:
    inline virtual ~Texture() {}
    
    virtual T evaluate(const Rayd& ray, const HitPoint& hitPoint) const = 0;
  };

  typedef Texture<Colord> Texturec;
}
