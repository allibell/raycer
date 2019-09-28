#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/primitives/Box.h"
#include "raycer/primitives/Sphere.h"
#include "raycer/materials/ReflectiveMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a perfectly reflective box") {
  auto box = std::make_shared<Box>(Vector3d::null(), Vector3d(1, 1, 0.1));
  auto material = std::make_shared<ReflectiveMaterial>();
  box->setMaterial(material);
  test->add(box);
}

GIVEN(RaycerFeatureTest, "a reflective box which filters the colors") {
  auto box = std::make_shared<Box>(Vector3d::null(), Vector3d(1, 1, 0.1));
  auto material = std::make_shared<ReflectiveMaterial>(
    std::make_shared<ConstantColorTexture>(Colord(1, 0, 0))
  );
  material->setReflectionCoefficient(0);
  material->setAmbientCoefficient(1);
  box->setMaterial(material);
  test->add(box);
}

GIVEN(RaycerFeatureTest, "a sphere behind the camera") {
  auto sphere = std::make_shared<Sphere>(Vector3d(0, 0, -4), 1);
  sphere->setMaterial(test->redDiffuse());
  test->add(sphere);
}

THEN(RaycerFeatureTest, "i should see the color filtered view through the box") {
  ASSERT_TRUE(test->colorPresent(Colord(1, 0, 0)));
}
