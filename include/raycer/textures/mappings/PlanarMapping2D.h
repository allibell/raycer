#pragma once

#include "raycer/textures/mappings/TextureMapping2D.h"

namespace raycer {
  class PlanarMapping2D : public TextureMapping2D {
  public:
    virtual void map(const HitPoint& hitPoint, double& s, double& t) const;
  };
}
