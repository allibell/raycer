#pragma once

#include "gmock/gmock.h"
#include "raycer/viewplanes/ViewPlane.h"
#include "test/mocks/MockDestructor.h"

namespace testing {
  class MockViewPlane : public raycer::ViewPlane, public MockDestructor {
  public:
  };
}
