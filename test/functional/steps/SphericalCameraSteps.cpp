#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/cameras/SphericalCamera.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a spherical camera") {
  test->setCamera(std::make_shared<SphericalCamera>());
}

WHEN(RaycerFeatureTest, "i set the spherical camera's field of view to maximum") {
  static_cast<SphericalCamera*>(test->camera().get())
    ->setFieldOfView(360_degrees, 180_degrees);
}
