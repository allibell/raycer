#include "gtest/gtest.h"
#include "test/abstract/AbstractViewPlaneTest.h"

namespace ViewPlaneTest {
  using namespace ::testing;
  using namespace raycer;
  
  INSTANTIATE_TYPED_TEST_CASE_P(
    ViewPlane,
    AbstractViewPlaneTest,
    ViewPlane
  );
}
