#include "gtest.h"
#include "raycer/viewplanes/PointShuffledViewPlane.h"
#include "test/abstract/AbstractViewPlaneIteratorTest.h"

namespace PointShuffledViewPlaneTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(PointShuffledViewPlane, ShouldInitialize) {
    PointShuffledViewPlane plane;
    ASSERT_EQ(0, plane.width());
    ASSERT_EQ(0, plane.height());
  }
  
  INSTANTIATE_TYPED_TEST_CASE_P(
    PointShuffled,
    AbstractViewPlaneIteratorTest,
    PointShuffledViewPlane
  );
}
