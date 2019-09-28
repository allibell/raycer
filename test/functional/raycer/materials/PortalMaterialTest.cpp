#include "test/functional/support/RaycerFeatureTest.h"

namespace PortalMaterialTest {
  using namespace ::testing;
  
  struct PortalMaterialTest : public RaycerFeatureTest {};
  
  TEST_F(PortalMaterialTest, ShouldNotBeVisibleByDefault) {
    given("a box portal");
    when("i look at the origin");
    then("i should see nothing");
  }
  
  TEST_F(PortalMaterialTest, ShouldBeTransparentByDefault) {
    given("a box portal");
    given("a sphere behind the box");
    when("i look at the origin");
    then("i should see the sphere");
  }

  TEST_F(PortalMaterialTest, ShouldRedirectRays) {
    given("a displaced sphere");
    given("a box portal which turns the rays towards the displaced sphere");
    when("i look at the origin");
    then("i should see the sphere");
  }
  
  TEST_F(PortalMaterialTest, ShouldNotBeTransparentWhenItRedirectsRays) {
    given("a box portal which turns the rays towards the displaced sphere");
    given("a sphere behind the box");
    when("i look at the origin");
    then("i should see nothing");
  }
  
  TEST_F(PortalMaterialTest, ShouldFilterColor) {
    given("a box portal which filters the colors");
    when("i look at the origin");
    then("i should see the color filtered view through the portal");
  }
}
