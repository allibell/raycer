#include "gtest/gtest.h"
#include "test/abstract/AbstractViewPlaneTest.h"
#include "raycer/viewplanes/PointShuffledViewPlane.h"

namespace PointShuffledViewPlaneTest {
  using namespace ::testing;
  using namespace raycer;
  
  INSTANTIATE_TYPED_TEST_CASE_P(
    PointShuffled,
    AbstractViewPlaneTest,
    PointShuffledViewPlane
  );
}
