#include "gtest/gtest.h"
#include "test/abstract/AbstractViewPlaneTest.h"
#include "raycer/viewplanes/PointInterlacedViewPlane.h"

namespace PointInterlacedViewPlaneTest {
  using namespace ::testing;
  using namespace raycer;
  
  INSTANTIATE_TYPED_TEST_CASE_P(
    PointInterlaced,
    AbstractViewPlaneTest,
    PointInterlacedViewPlane
  );
}
