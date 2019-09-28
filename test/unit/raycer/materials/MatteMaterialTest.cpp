#include "gtest.h"
#include "raycer/materials/MatteMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

namespace MatteMaterialTest {
  using namespace raycer;

  TEST(MatteMaterial, ShouldInitialize) {
    MatteMaterial material;
    ASSERT_EQ(nullptr, material.diffuseTexture());
  }

  TEST(MatteMaterial, ShouldInitializeWithDiffuseTexture) {
    auto texture = std::make_shared<ConstantColorTexture>(Colord(0, 1, 0));
    MatteMaterial material(texture);
    ASSERT_EQ(texture, material.diffuseTexture());
  }
  
  TEST(MatteMaterial, ShouldSetDiffuseTexture) {
    MatteMaterial material;

    auto texture = std::make_shared<ConstantColorTexture>(Colord(0, 1, 0));
    material.setDiffuseTexture(texture);
    ASSERT_EQ(texture, material.diffuseTexture());
  }
  
  TEST(MatteMaterial, ShouldSetAmbientCoefficient) {
    MatteMaterial material;
    material.setAmbientCoefficient(0.6);
    ASSERT_EQ(0.6, material.ambientCoefficient());
  }
  
  TEST(MatteMaterial, ShouldSetDiffuseCoefficient) {
    MatteMaterial material;
    material.setDiffuseCoefficient(0.6);
    ASSERT_EQ(0.6, material.diffuseCoefficient());
  }
}
