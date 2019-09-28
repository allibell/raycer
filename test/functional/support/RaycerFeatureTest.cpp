#include "test/functional/support/RaycerFeatureTest.h"

#include "raycer/primitives/Scene.h"
#include "raycer/Raycer.h"
#include "raycer/cameras/PinholeCamera.h"
#include "raycer/materials/MatteMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

#include "test/helpers/ImageViewer.h"

namespace testing {
  using namespace raycer;

  RaycerFeatureTest::RaycerFeatureTest()
    : FeatureTest<RaycerFeatureTest>(),
      m_camera(0),
      m_raycer(0),
      m_buffer(200, 150)
  {
    previousObjectSize = 0;
  }

  void RaycerFeatureTest::beforeThen() {
    render();
  }

  void RaycerFeatureTest::SetUp() {
    m_scene = new Scene(Colord(1, 1, 1));
  }

  void RaycerFeatureTest::TearDown() {
    delete m_scene;
  }

  void RaycerFeatureTest::add(std::shared_ptr<Primitive> primitive) {
    m_scene->add(primitive);
  }

  Scene* RaycerFeatureTest::scene() const {
    return m_scene;
  }

  std::shared_ptr<Camera> RaycerFeatureTest::camera() {
    if (!m_camera)
      m_camera = std::make_shared<PinholeCamera>();
    return m_camera;
  }

  void RaycerFeatureTest::setCamera(const Vector3d& position, const Vector3d& lookAt) {
    setCamera(std::make_shared<PinholeCamera>(position, lookAt));
  }

  void RaycerFeatureTest::setCamera(std::shared_ptr<Camera> camera) {
    m_camera = camera;
  }

  void RaycerFeatureTest::setView(const Vector3d& position, const Vector3d& lookAt) {
    camera()->setPosition(position);
    camera()->setTarget(lookAt);
  }

  void RaycerFeatureTest::render() {
    m_raycer = std::make_shared<Raycer>(m_camera, m_scene);
    m_raycer->render(m_buffer);
  }

  void RaycerFeatureTest::cancel() {
    camera()->cancel();
  }

  void RaycerFeatureTest::clear() {
    m_buffer.clear();
  }

  const Buffer<unsigned int>& RaycerFeatureTest::buffer() const {
    return m_buffer;
  }

  bool RaycerFeatureTest::colorPresent(const Colord& color) const {
    return colorCount(color) > 0;
  }

  int RaycerFeatureTest::colorCount(const Colord& color) const {
    int result = 0;
    for (int i = 0; i != m_buffer.width(); ++i) {
      for (int j = 0; j != m_buffer.height(); ++j) {
        if (m_buffer[j][i] == color.rgb()) {
          result++;
        }
      }
    }
    return result;
  }

  unsigned int RaycerFeatureTest::colorAt(int x, int y) const {
    return m_buffer[y][x];
  }

  void RaycerFeatureTest::show() const {
    ImageViewer viewer(m_buffer);
    viewer.show();
  }

  std::shared_ptr<Material> RaycerFeatureTest::redDiffuse() const {
    return std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(1, 0, 0)));
  }

  void RaycerFeatureTest::lookAtOrigin() {
    setView(Vector3d(0, 0, -5), Vector3d::null());
  }

  void RaycerFeatureTest::lookAway() {
    setView(Vector3d(0, 0, -20), Vector3d(0, 0, -25));
  }

  void RaycerFeatureTest::goFarAway() {
    setView(Vector3d(0, 0, -30), Vector3d::null());
  }

  bool RaycerFeatureTest::objectVisible() const {
    return colorPresent(Colord(1, 0, 0));
  }

  int RaycerFeatureTest::objectSize() const {
    return colorCount(Colord(1, 0, 0));
  }
}
