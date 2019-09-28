#include "gtest/gtest.h"
#include "test/abstract/AbstractViewPlaneTest.h"
#include "raycer/viewplanes/RowShuffledViewPlane.h"

namespace RowShuffledViewPlaneTest {
  using namespace ::testing;
  using namespace raycer;
  
  INSTANTIATE_TYPED_TEST_CASE_P(
    RowShuffled,
    AbstractViewPlaneTest,
    RowShuffledViewPlane
  );
}
