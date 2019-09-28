#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "raycer/primitives/Scene.h"

using namespace testing;

GIVEN(RaycerFeatureTest, "an empty scene with blue background") {
  test->scene()->setBackground(Colord(0.4, 0.8, 1));
}

THEN(RaycerFeatureTest, "i should see only blue") {
  ASSERT_TRUE(test->colorPresent(Colord(0.4, 0.8, 1)));
}
