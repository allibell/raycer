#include "gtest/gtest.h"
#include "test/abstract/AbstractViewPlaneTest.h"
#include "raycer/viewplanes/TiledViewPlane.h"

namespace TiledViewPlaneTest {
  using namespace ::testing;
  using namespace raycer;
  
  INSTANTIATE_TYPED_TEST_CASE_P(
    Tiled,
    AbstractViewPlaneTest,
    TiledViewPlane
  );
}
