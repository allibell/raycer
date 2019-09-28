#include "test/functional/support/RaycerFeatureTest.h"

namespace BoxTest {
  using namespace ::testing;
  
  class BoxTest : public RaycerFeatureTest {};
  
  TEST_F(BoxTest, ShouldBeVisibileInFrontOfTheCamera) {
    given("a centered box");
    when("i look at the origin");
    then("i should see the box");
  }
  
  TEST_F(BoxTest, ShouldNotBeVisibileOutsideOfViewFrustum) {
    given("a displaced box");
    when("i look at the origin");
    then("i should not see the box");
  }

  TEST_F(BoxTest, ShouldNotBeVisibileBehindTheCamera) {
    given("a centered box");
    when("i look away from the origin");
    then("i should not see the box");
  }
}
