#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "test/helpers/ShapeRecognition.h"

#include "raycer/primitives/Rectangle.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered rectangle") {
  auto rectangle = std::make_shared<Rectangle>(Vector3d(-1, -1, 0), Vector3d(2, 0, 0), Vector3d(0, 2, 0));
  rectangle->setMaterial(test->redDiffuse());
  test->add(rectangle);
}

GIVEN(RaycerFeatureTest, "a displaced rectangle") {
  auto rectangle = std::make_shared<Rectangle>(Vector3d(-1, 20, 0), Vector3d(2, 0, 0), Vector3d(0, 2, 0));
  rectangle->setMaterial(test->redDiffuse());
  test->add(rectangle);
}

THEN(RaycerFeatureTest, "i should see the rectangle") {
  ShapeRecognition rec;
  ASSERT_TRUE(rec.recognizeRect(test->buffer()));
}

THEN(RaycerFeatureTest, "i should not see the rectangle") {
  ShapeRecognition rec;
  ASSERT_FALSE(rec.recognizeRect(test->buffer()));
}
