#pragma once

#include "core/Factory.h"
#include "core/Singleton.h"
#include "raycer/cameras/Camera.h"

namespace raycer {
  typedef Singleton<Factory<Camera>> CameraFactory;
}
