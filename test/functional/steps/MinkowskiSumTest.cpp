#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "test/helpers/ShapeRecognition.h"

#include "raycer/primitives/MinkowskiSum.h"
#include "raycer/primitives/Instance.h"
#include "raycer/primitives/Box.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered minkowski sum with two boxes") {
  auto hull = std::make_shared<MinkowskiSum>();
  hull->add(std::make_shared<Box>(Vector3d(0, 0, 0), Vector3d(0.25, 0.25, 0.25)));
  hull->add(std::make_shared<Box>(Vector3d(0, 0, 0), Vector3d(0.25, 0.25, 0.25)));
  hull->setMaterial(test->redDiffuse());
  
  test->add(hull);
}

GIVEN(RaycerFeatureTest, "a displaced minkowski sum with two boxes") {
  auto hull = std::make_shared<MinkowskiSum>();
  hull->add(std::make_shared<Box>(Vector3d(0, 0, 0), Vector3d(0.25, 0.25, 0.25)));
  hull->add(std::make_shared<Box>(Vector3d(0, 0, 0), Vector3d(0.25, 0.25, 0.25)));
  hull->setMaterial(test->redDiffuse());

  auto instance = std::make_shared<Instance>(hull);
  instance->setMatrix(Matrix4d::translate(20, 0, 0));
  test->add(instance);
}
