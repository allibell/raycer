#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/cameras/FishEyeCamera.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a fish-eye camera") {
  test->setCamera(std::make_shared<FishEyeCamera>());
}

WHEN(RaycerFeatureTest, "i set the fish-eye camera's field of view to maximum") {
  static_cast<FishEyeCamera*>(test->camera().get())->setFieldOfView(360_degrees);
}

THEN(RaycerFeatureTest, "i should see a black ring around the image") {
  ASSERT_TRUE(test->colorPresent(Colord::black()));
  ASSERT_TRUE(test->colorPresent(Colord::white()));
}
