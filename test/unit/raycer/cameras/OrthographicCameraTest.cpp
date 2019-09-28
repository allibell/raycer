#include "gtest.h"
#include "raycer/cameras/OrthographicCamera.h"
#include "raycer/Raycer.h"
#include "raycer/primitives/Scene.h"
#include "core/Buffer.h"

namespace OrthographicCameraTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(OrthographicCamera, ShouldConstructWithoutParameters) {
    OrthographicCamera camera;
  }
  
  TEST(OrthographicCamera, ShouldConstructWithParameters) {
    OrthographicCamera camera(Vector3d(0, 0, 1), Vector3d::null());
  }
  
  TEST(OrthographicCamera, ShouldRender) {
    OrthographicCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    Scene scene(Colord::white());
    auto raycer = std::make_shared<Raycer>(&scene);
    Buffer<unsigned int> buffer(1, 1);
    camera.render(raycer, buffer);
    ASSERT_EQ(Colord::white().rgb(), buffer[0][0]);
  }
  
  TEST(OrthographicCamera, ShouldGetRayForPixelWithUninitializedViewPlane) {
    OrthographicCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    Rayd ray = camera.rayForPixel(0, 0);
    ASSERT_EQ(Vector3d(0, 0, 0), ray.origin());
    ASSERT_EQ(Vector3d(0, 0, 1), ray.direction());
  }
  
  TEST(OrthographicCamera, ShouldGetRayForPixelWithInitializedViewPlane) {
    OrthographicCamera camera(Vector3d(0, 0, -1), Vector3d::null());
    auto raycer = std::make_shared<Raycer>(new Scene(Colord::white()));
    Buffer<unsigned int> buffer(1, 1);
    camera.render(raycer, buffer);
    
    Rayd ray = camera.rayForPixel(0, 0);
    ASSERT_EQ(Vector3d(0, 0, 0), ray.origin());
    ASSERT_EQ(Vector3d(0, 0, 1), ray.direction());
  }
}
