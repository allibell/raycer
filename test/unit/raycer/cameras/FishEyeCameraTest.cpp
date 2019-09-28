#include "gtest.h"
#include "raycer/cameras/FishEyeCamera.h"
#include "raycer/Raycer.h"
#include "raycer/primitives/Scene.h"
#include "core/Buffer.h"

namespace FishEyeCameraTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(FishEyeCamera, ShouldConstructWithoutParameters) {
    FishEyeCamera camera;
    ASSERT_NEAR(120, camera.fieldOfView().degrees(), 0.001);
  }
  
  TEST(FishEyeCamera, ShouldConstructWithParameters) {
    FishEyeCamera camera(Vector3d(0, 0, 1), Vector3d::null());
    ASSERT_NEAR(120, camera.fieldOfView().degrees(), 0.001);
  }
  
  TEST(FishEyeCamera, ShouldConstructWithFieldOfView) {
    FishEyeCamera camera(360_degrees);
    ASSERT_NEAR(360, camera.fieldOfView().degrees(), 0.001);
  }
  
  TEST(FishEyeCamera, ShouldSetFieldOfView) {
    FishEyeCamera camera;
    camera.setFieldOfView(200_degrees);
    ASSERT_NEAR(200, camera.fieldOfView().degrees(), 0.001);
  }
  
  TEST(FishEyeCamera, ShouldRender) {
    FishEyeCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    Scene scene(Colord::white());
    auto raycer = std::make_shared<Raycer>(&scene);
    Buffer<unsigned int> buffer(1, 1);
    camera.render(raycer, buffer);
    // This is black because of the black rounded border around fish eye images
    ASSERT_EQ(Colord::black().rgb(), buffer[0][0]);
  }
  
  TEST(FishEyeCamera, ShouldGetRayForPixelWithUninitializedViewPlane) {
    FishEyeCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    Rayd ray = camera.rayForPixel(0, 0);
    ASSERT_EQ(Vector3d(0, 0, -1), ray.origin());
    ASSERT_TRUE(ray.direction().isUndefined());
  }
  
  TEST(FishEyeCamera, ShouldGetRayForPixelWithInitializedViewPlane) {
    FishEyeCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    auto raycer = std::make_shared<Raycer>(new Scene(Colord::white()));
    Buffer<unsigned int> buffer(1, 1);
    camera.render(raycer, buffer);

    Rayd ray = camera.rayForPixel(0, 0);
    ASSERT_EQ(Vector3d(0, 0, -1), ray.origin());
    ASSERT_TRUE(ray.direction().isUndefined());
  }
}
