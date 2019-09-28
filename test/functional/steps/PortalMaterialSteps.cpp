#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/primitives/Box.h"
#include "raycer/primitives/Sphere.h"
#include "raycer/materials/PortalMaterial.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a box portal") {
  auto box = std::make_shared<Box>(Vector3d::null(), Vector3d(1, 1, 0.1));
  auto material = std::make_shared<PortalMaterial>(Matrix3d(), Colord::white());
  box->setMaterial(material);
  test->add(box);
}

GIVEN(RaycerFeatureTest, "a box portal which turns the rays towards the displaced sphere") {
  auto box = std::make_shared<Box>(Vector3d::null(), Vector3d(1, 1, 0.1));
  auto material = std::make_shared<PortalMaterial>(Matrix3d::rotateX(Angled::fromRadians(0.79)), Colord::white());
  box->setMaterial(material);
  test->add(box);
}

GIVEN(RaycerFeatureTest, "a box portal which filters the colors") {
  auto box = std::make_shared<Box>(Vector3d::null(), Vector3d(1, 1, 0.1));
  auto material = std::make_shared<PortalMaterial>(Matrix3d(), Colord(1, 0, 0));
  box->setMaterial(material);
  test->add(box);
}

GIVEN(RaycerFeatureTest, "a sphere behind the box") {
  auto sphere = std::make_shared<Sphere>(Vector3d(0, 0, 4), 1);
  sphere->setMaterial(test->redDiffuse());
  test->add(sphere);
}

THEN(RaycerFeatureTest, "i should see the color filtered view through the portal") {
  ASSERT_TRUE(test->colorPresent(Colord(1, 0, 0)));
}
