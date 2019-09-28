#include "gtest/gtest.h"
#include "test/abstract/AbstractViewPlaneTest.h"
#include "raycer/viewplanes/RowInterlacedViewPlane.h"

namespace RowInterlacedViewPlaneTest {
  using namespace ::testing;
  using namespace raycer;
  
  INSTANTIATE_TYPED_TEST_CASE_P(
    RowInterlaced,
    AbstractViewPlaneTest,
    RowInterlacedViewPlane
  );
}
