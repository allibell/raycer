#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

using namespace testing;

GIVEN(RaycerFeatureTest, "a blank canvas") {
  test->clear();
}

GIVEN(RaycerFeatureTest, "an empty scene") {
  // do nothing
  (void)test;
}

WHEN(RaycerFeatureTest, "the render process is canceled") {
  test->cancel();
}

THEN(RaycerFeatureTest, "i should see something") {
  ASSERT_TRUE(test->objectVisible());
}

THEN(RaycerFeatureTest, "i should see nothing") {
  ASSERT_FALSE(test->objectVisible());
}

THEN(RaycerFeatureTest, "show me") {
  test->show();
}
