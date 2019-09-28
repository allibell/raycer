#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/cameras/OrthographicCamera.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "an orthographic camera") {
  test->setCamera(std::make_shared<OrthographicCamera>());
}
