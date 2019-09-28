#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "test/helpers/ShapeRecognition.h"

#include "raycer/primitives/ConvexHull.h"
#include "raycer/primitives/Instance.h"
#include "raycer/primitives/Box.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered convex hull with two boxes side by side") {
  auto hull = std::make_shared<ConvexHull>();
  hull->add(std::make_shared<Box>(Vector3d(-1, 0, 0), Vector3d(0.25, 0.25, 0.25)));
  hull->add(std::make_shared<Box>(Vector3d( 1, 0, 0), Vector3d(0.25, 0.25, 0.25)));
  hull->setMaterial(test->redDiffuse());
  
  test->add(hull);
}

GIVEN(RaycerFeatureTest, "a displaced convex hull with two boxes side by side") {
  auto hull = std::make_shared<ConvexHull>();
  hull->add(std::make_shared<Box>(Vector3d(-1, 0, 0), Vector3d(0.25, 0.25, 0.25)));
  hull->add(std::make_shared<Box>(Vector3d( 1, 0, 0), Vector3d(0.25, 0.25, 0.25)));
  hull->setMaterial(test->redDiffuse());

  auto instance = std::make_shared<Instance>(hull);
  instance->setMatrix(Matrix4d::translate(20, 0, 0));
  test->add(instance);
}
