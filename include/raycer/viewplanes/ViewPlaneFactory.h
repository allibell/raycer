#pragma once

#include "core/Factory.h"
#include "core/Singleton.h"
#include "raycer/viewplanes/ViewPlane.h"

namespace raycer {
  typedef Singleton<Factory<ViewPlane>> ViewPlaneFactory;
}
