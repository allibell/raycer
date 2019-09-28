#include "gtest.h"
#include "raycer/cameras/PinholeCamera.h"
#include "raycer/Raycer.h"
#include "raycer/primitives/Scene.h"
#include "core/Buffer.h"

namespace PinholeCameraTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(PinholeCamera, ShouldConstructWithoutParameters) {
    PinholeCamera camera;
    ASSERT_EQ(5, camera.distance());
    ASSERT_EQ(1, camera.zoom());
  }
  
  TEST(PinholeCamera, ShouldConstructWithParameters) {
    PinholeCamera camera(Vector3d(0, 0, 1), Vector3d::null());
    ASSERT_EQ(5, camera.distance());
    ASSERT_EQ(1, camera.zoom());
  }
  
  TEST(PinholeCamera, ShouldSetDistance) {
    PinholeCamera camera;
    camera.setDistance(20);
    ASSERT_EQ(20, camera.distance());
  }
  
  TEST(PinholeCamera, ShouldSetZoom) {
    PinholeCamera camera;
    camera.setZoom(2);
    ASSERT_EQ(2, camera.zoom());
  }
  
  TEST(PinholeCamera, ShouldRender) {
    PinholeCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    Scene scene(Colord::white());
    auto raycer = std::make_shared<Raycer>(&scene);
    Buffer<unsigned int> buffer(1, 1);
    camera.render(raycer, buffer);
    ASSERT_EQ(Colord::white().rgb(), buffer[0][0]);
  }
  
  TEST(PinholeCamera, ShouldSetViewplanePixelSize) {
    PinholeCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    Scene scene(Colord::white());
    auto raycer = std::make_shared<Raycer>(&scene);
    Buffer<unsigned int> buffer(1, 1);

    camera.setZoom(2);
    camera.render(raycer, buffer);
    ASSERT_EQ(0.5, camera.viewPlane()->pixelSize());
  }
  
  TEST(PinholeCamera, ShouldGetRayForPixelWithUninitializedViewPlane) {
    PinholeCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    Rayd ray = camera.rayForPixel(0, 0);
    ASSERT_EQ(Vector3d(0, 0, -6), ray.origin());
    ASSERT_EQ(Vector3d(0, 0, 1), ray.direction());
  }
  
  TEST(PinholeCamera, ShouldGetRayForPixelWithInitializedViewPlane) {
    PinholeCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    auto raycer = std::make_shared<Raycer>(new Scene(Colord::white()));
    Buffer<unsigned int> buffer(1, 1);
    camera.render(raycer, buffer);

    Rayd ray = camera.rayForPixel(0, 0);
    ASSERT_EQ(Vector3d(0, 0, -6), ray.origin());
    ASSERT_EQ(Vector3d(0, 0, 1), ray.direction());
  }
}
