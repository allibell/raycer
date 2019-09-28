#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/primitives/Triangle.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered triangle") {
  auto triangle = std::make_shared<Triangle>(Vector3d(-1, -1, 0), Vector3d(-1, 1, 0), Vector3d(1, -1, 0));
  triangle->setMaterial(test->redDiffuse());
  test->add(triangle);
}

GIVEN(RaycerFeatureTest, "a displaced triangle") {
  auto triangle = std::make_shared<Triangle>(Vector3d(-1, 20, 0), Vector3d(-1, 21, 0), Vector3d(1, 20, 0));
  triangle->setMaterial(test->redDiffuse());
  test->add(triangle);
}

THEN(RaycerFeatureTest, "i should see the triangle") {
  ASSERT_TRUE(test->objectVisible());
}

THEN(RaycerFeatureTest, "i should not see the triangle") {
  ASSERT_FALSE(test->objectVisible());
}
