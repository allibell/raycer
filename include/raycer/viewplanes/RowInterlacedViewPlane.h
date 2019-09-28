#pragma once

#include "raycer/viewplanes/ViewPlane.h"

namespace raycer {
  class RowInterlacedViewPlane : public ViewPlane {
  public:
    virtual Iterator begin(const Recti& rect) const;
  };
}
