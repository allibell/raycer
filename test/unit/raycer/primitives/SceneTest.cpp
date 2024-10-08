#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "raycer/primitives/Scene.h"
#include "raycer/lights/PointLight.h"

namespace SceneTest {
  using namespace ::testing;
  using namespace raycer;

  TEST(Scene, ShouldInitialize) {
    Scene scene;
    ASSERT_EQ(Colord::white(), scene.ambient());
  }

  TEST(Scene, ShouldInitializeAmbientColor) {
    Scene scene(Colord::white());
    ASSERT_EQ(Colord::white(), scene.ambient());
  }

  TEST(Scene, ShouldInitializeBackgroundColor) {
    Scene scene(Colord::white());
    ASSERT_EQ(Colord::white(), scene.background());
  }

  TEST(Scene, ShouldHaveNoLightByDefault) {
    Scene scene(Colord::white());
    ASSERT_TRUE(scene.lights().empty());
  }

  TEST(Scene, ShouldAddLight) {
    Scene scene(Colord::white());
    auto light = std::make_shared<PointLight>(Vector3d(), Colord::white());
    scene.addLight(light);
    ASSERT_FALSE(scene.lights().empty());
    ASSERT_EQ(light, scene.lights().front());
  }
}
