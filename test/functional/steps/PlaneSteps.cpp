#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/primitives/Plane.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered plane") {
  auto plane = std::make_shared<Plane>(Vector3d(0, 0, 1), 0);
  plane->setMaterial(test->redDiffuse());
  test->add(plane);
}

THEN(RaycerFeatureTest, "i should see the plane") {
  ASSERT_TRUE(test->objectVisible());
}

THEN(RaycerFeatureTest, "i should not see the plane") {
  ASSERT_FALSE(test->objectVisible());
}

THEN(RaycerFeatureTest, "the plane should cover the whole image") {
  ASSERT_FALSE(test->colorPresent(Colord::white()));
}
