#include "gtest.h"
#include "raycer/materials/PhongMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

namespace PhongMaterialTest {
  using namespace raycer;

  TEST(PhongMaterial, ShouldInitialize) {
    PhongMaterial material;
    ASSERT_EQ(Colord::white(), material.specularColor());
  }

  TEST(PhongMaterial, ShouldInitializeWithDiffuseTexture) {
    auto texture = std::make_shared<ConstantColorTexture>(Colord(0, 1, 0));
    PhongMaterial material(texture);
    ASSERT_EQ(texture, material.diffuseTexture());
    ASSERT_EQ(Colord::white(), material.specularColor());
  }
  
  TEST(PhongMaterial, ShouldSetHighlightColor) {
    PhongMaterial material;
    material.setSpecularColor(Colord(0, 1, 0));
    ASSERT_EQ(Colord(0, 1, 0), material.specularColor());
  }
}
