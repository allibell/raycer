#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/cameras/PinholeCamera.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a pinhole camera") {
  // do nothing, the pinhole camera is the default
  (void)test;
}

WHEN(RaycerFeatureTest, "i set the pinhole camera's view plane distance to a very small value") {
  static_cast<PinholeCamera*>(test->camera().get())->setDistance(1);
}

WHEN(RaycerFeatureTest, "i set the pinhole camera's view plane distance to a normal value") {
  static_cast<PinholeCamera*>(test->camera().get())->setDistance(5);
}
