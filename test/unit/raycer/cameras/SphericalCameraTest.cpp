#include "gtest.h"
#include "raycer/cameras/SphericalCamera.h"
#include "raycer/Raycer.h"
#include "raycer/primitives/Scene.h"
#include "core/Buffer.h"

#include "test/helpers/ImageViewer.h"

namespace SphericalCameraTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(SphericalCamera, ShouldConstructWithoutParameters) {
    SphericalCamera camera;
    ASSERT_NEAR(180, camera.horizontalFieldOfView().degrees(), 0.001);
    ASSERT_NEAR(120, camera.verticalFieldOfView().degrees(), 0.001);
  }
  
  TEST(SphericalCamera, ShouldConstructWithParameters) {
    SphericalCamera camera(Vector3d(0, 0, 1), Vector3d::null());
    ASSERT_NEAR(180, camera.horizontalFieldOfView().degrees(), 0.001);
    ASSERT_NEAR(120, camera.verticalFieldOfView().degrees(), 0.001);
  }
  
  TEST(SphericalCamera, ShouldConstructWithFieldOfViews) {
    SphericalCamera camera(200_degrees, 90_degrees);
    ASSERT_NEAR(200, camera.horizontalFieldOfView().degrees(), 0.001);
    ASSERT_NEAR(90, camera.verticalFieldOfView().degrees(), 0.001);
  }
  
  TEST(SphericalCamera, ShouldSetHorizontalFieldOfView) {
    SphericalCamera camera;
    camera.setHorizontalFieldOfView(200_degrees);
    ASSERT_NEAR(200, camera.horizontalFieldOfView().degrees(), 0.001);
  }
  
  TEST(SphericalCamera, ShouldSetVerticalFieldOfView) {
    SphericalCamera camera;
    camera.setVerticalFieldOfView(140_degrees);
    ASSERT_NEAR(140, camera.verticalFieldOfView().degrees(), 0.001);
  }
  
  TEST(SphericalCamera, ShouldRender) {
    auto camera = std::make_shared<SphericalCamera>(Vector3d(0, 0, -1), Vector3d::null());
    Scene scene(Colord::white());
    auto raycer = std::make_shared<Raycer>(camera, &scene);
    Buffer<unsigned int> buffer(1, 1);
    raycer->render(buffer);
    ASSERT_EQ(Colord::white().rgb(), buffer[0][0]);
  }
  
  TEST(SphericalCamera, ShouldGetRayForPixelWithUninitializedViewPlane) {
    SphericalCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    Rayd ray = camera.rayForPixel(0, 0);
    ASSERT_EQ(Vector3d(0, 0, -6), ray.origin());
    ASSERT_TRUE(ray.direction().isUndefined());
  }
  
  TEST(SphericalCamera, ShouldGetRayForPixelWithInitializedViewPlane) {
    SphericalCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    auto raycer = std::make_shared<Raycer>(new Scene(Colord::white()));

    Rayd ray = camera.rayForPixel(0, 0);
    ASSERT_EQ(Vector3d(0, 0, -6), ray.origin());
    ASSERT_TRUE(ray.direction().isUndefined());
  }
}
