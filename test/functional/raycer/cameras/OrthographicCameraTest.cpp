#include "test/functional/support/RaycerFeatureTest.h"

namespace OrthographicCameraTest {
  using namespace ::testing;
  
  struct OrthographicCameraTest : public RaycerFeatureTest {};
  
  TEST_F(OrthographicCameraTest, ShouldBeVisibileInFrontOfTheCamera) {
    given("an orthographic camera");
    given("a centered sphere");
    when("i look at the origin");
    then("i should see the sphere");
  }
  
  TEST_F(OrthographicCameraTest, ShouldNotBeVisibileOutsideOfView) {
    given("an orthographic camera");
    given("a displaced sphere");
    when("i look at the origin");
    then("i should not see the sphere");
  }

  TEST_F(OrthographicCameraTest, ShouldNotBeVisibileBehindTheCamera) {
    given("an orthographic camera");
    given("a centered sphere");
    when("i look away from the origin");
    then("i should not see the sphere");
  }
  
  TEST_F(OrthographicCameraTest, ShouldNotShrinkSizeOfObjectWithLargerDistance) {
    given("an orthographic camera");
    given("a centered sphere");
    when("i look at the origin");
    then("i should see the sphere with size S");
    when("i go far away from the origin");
    then("i should see the sphere with size S");
  }

  TEST_F(OrthographicCameraTest, ShouldGrowSizeOfObjectWithLargerZoom) {
    given("an orthographic camera");
    given("a centered sphere");
    when("i look at the origin");
    then("i should see the sphere with size S");
    when("i zoom in");
    then("i should see the sphere with size larger than S");
  }

  TEST_F(OrthographicCameraTest, ShouldShrinkSizeOfObjectWithSmallerZoom) {
    given("an orthographic camera");
    given("a centered sphere");
    when("i look at the origin");
    then("i should see the sphere with size S");
    when("i zoom out");
    then("i should see the sphere with size smaller than S");
  }

  TEST_F(OrthographicCameraTest, ShouldNotRenderWhenCanceled) {
    given("a blank canvas");
    given("an orthographic camera");
    when("the render process is canceled");
    when("i look at the origin");
    then("i should see nothing");
  }
}
