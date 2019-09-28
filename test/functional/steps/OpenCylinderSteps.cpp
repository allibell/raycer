#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "test/helpers/ShapeRecognition.h"

#include "raycer/primitives/OpenCylinder.h"
#include "raycer/primitives/Instance.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered open cylinder") {
  auto cylinder = std::make_shared<OpenCylinder>(1, 2);
  cylinder->setMaterial(test->redDiffuse());
  test->add(cylinder);
}

GIVEN(RaycerFeatureTest, "a displaced open cylinder") {
  auto cylinder = std::make_shared<OpenCylinder>(1, 2);
  cylinder->setMaterial(test->redDiffuse());
  auto instance = std::make_shared<Instance>(cylinder);
  instance->setMatrix(Matrix4d::translate(0, 20, 0));
  test->add(instance);
}

GIVEN(RaycerFeatureTest, "an open cylinder rotated 90 degrees around the x axis") {
  auto cylinder = std::make_shared<OpenCylinder>(1, 2);
  cylinder->setMaterial(test->redDiffuse());
  auto instance = std::make_shared<Instance>(cylinder);
  instance->setMatrix(Matrix3d::rotateX(90_degrees));
  test->add(instance);
}

THEN(RaycerFeatureTest, "i should see the open cylinder") {
  ShapeRecognition rec;
  // This should be a different shape than circle
  ASSERT_TRUE(rec.recognizeCircle(test->buffer()));
}

THEN(RaycerFeatureTest, "i should not see the open cylinder") {
  ShapeRecognition rec;
  ASSERT_FALSE(rec.recognizeCircle(test->buffer()));
}

THEN(RaycerFeatureTest, "i should see a ring") {
  ShapeRecognition rec;
  // This should be a different shape than circle, since it is a ring. The
  // ShapeRecognition class only looks at the outlines.
  ASSERT_TRUE(rec.recognizeCircle(test->buffer()));
}
