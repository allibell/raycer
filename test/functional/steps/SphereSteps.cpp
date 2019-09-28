#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "test/helpers/ShapeRecognition.h"

#include "raycer/primitives/Sphere.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered sphere") {
  auto sphere = std::make_shared<Sphere>(Vector3d::null(), 1);
  sphere->setMaterial(test->redDiffuse());
  test->add(sphere);
}

GIVEN(RaycerFeatureTest, "a displaced sphere") {
  auto sphere = std::make_shared<Sphere>(Vector3d(0, 20, 0), 1);
  sphere->setMaterial(test->redDiffuse());
  test->add(sphere);
}

THEN(RaycerFeatureTest, "i should see the sphere") {
  ShapeRecognition rec;
  ASSERT_TRUE(rec.recognizeCircle(test->buffer()));
}

THEN(RaycerFeatureTest, "i should see the sphere with size S") {
  ASSERT_TRUE(test->objectVisible());
  if (test->previousObjectSize) {
    ASSERT_EQ(test->previousObjectSize, test->objectSize());
  } else {
    test->previousObjectSize = test->objectSize();
  }
}

THEN(RaycerFeatureTest, "i should see the sphere with size smaller than S") {
  ASSERT_TRUE(test->objectVisible());
  ASSERT_TRUE(test->previousObjectSize > test->objectSize());
}

THEN(RaycerFeatureTest, "i should see the sphere with size larger than S") {
  ASSERT_TRUE(test->objectVisible());
  ASSERT_TRUE(test->previousObjectSize < test->objectSize());
}

THEN(RaycerFeatureTest, "i should not see the sphere") {
  ShapeRecognition rec;
  ASSERT_FALSE(rec.recognizeCircle(test->buffer()));
}
