#pragma once

#include "raycer/viewplanes/ViewPlane.h"

namespace raycer {
  class PointShuffledViewPlane : public ViewPlane {
  public:
    virtual Iterator begin(const Recti& rect) const;
  };
}
