#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "test/helpers/ShapeRecognition.h"

#include "raycer/primitives/Torus.h"
#include "raycer/primitives/Instance.h"

#include "core/math/Matrix.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered torus") {
  auto torus = std::make_shared<Torus>(1, 0.5);
  torus->setMaterial(test->redDiffuse());
  test->add(torus);
}

GIVEN(RaycerFeatureTest, "a 90 degree rotated torus") {
  auto torus = std::make_shared<Torus>(1, 0.5);
  auto instance = std::make_shared<Instance>(torus);
  instance->setMatrix(Matrix3d::rotateX(90_degrees));
  
  instance->setMaterial(test->redDiffuse());
  test->add(instance);
}

THEN(RaycerFeatureTest, "i should see the torus") {
  ShapeRecognition rec;
  ASSERT_TRUE(rec.recognizeCircle(test->buffer()));
}

THEN(RaycerFeatureTest, "i should see the torus with a hole in the middle") {
  ASSERT_TRUE(test->objectVisible());
  ASSERT_EQ(Colord::white().rgb(), test->colorAt(100, 75));
}

THEN(RaycerFeatureTest, "i should not see the torus") {
  ShapeRecognition rec;
  ASSERT_FALSE(rec.recognizeCircle(test->buffer()));
}
