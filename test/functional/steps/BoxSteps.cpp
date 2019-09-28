#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "test/helpers/ShapeRecognition.h"

#include "raycer/primitives/Box.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered box") {
  auto box = std::make_shared<Box>(Vector3d::null(), Vector3d(1, 1, 1));
  box->setMaterial(test->redDiffuse());
  test->add(box);
}

GIVEN(RaycerFeatureTest, "a displaced box") {
  auto box = std::make_shared<Box>(Vector3d(0, 20, 0), Vector3d(1, 1, 1));
  box->setMaterial(test->redDiffuse());
  test->add(box);
}

THEN(RaycerFeatureTest, "i should see the box") {
  ShapeRecognition rec;
  ASSERT_TRUE(rec.recognizeRect(test->buffer()));
}

THEN(RaycerFeatureTest, "i should not see the box") {
  ShapeRecognition rec;
  ASSERT_FALSE(rec.recognizeRect(test->buffer()));
}
