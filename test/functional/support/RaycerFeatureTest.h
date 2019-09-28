#ifndef RAYCER_FEATURE_TEST_H
#define RAYCER_FEATURE_TEST_H

#include "test/functional/support/FeatureTest.h"

#include "core/math/Vector.h"
#include "core/Color.h"
#include "core/Buffer.h"
#include <memory>

namespace raycer {
  class Primitive;
  class Camera;
  class Raycer;
  class Material;
  class Scene;
}

namespace testing {
  class RaycerFeatureTest : public FeatureTest<RaycerFeatureTest> {
  protected:
    virtual void SetUp();
    virtual void TearDown();

    virtual void beforeThen();

  public:
    RaycerFeatureTest();

    void add(std::shared_ptr<raycer::Primitive> primitive);
    raycer::Scene* scene() const;
    std::shared_ptr<raycer::Camera> camera();
    void setCamera(std::shared_ptr<raycer::Camera> camera);
    void setCamera(const Vector3d& position, const Vector3d& lookAt);
    void setView(const Vector3d& position, const Vector3d& lookAt);
    void render();
    void cancel();

    const Buffer<unsigned int>& buffer() const;
    void clear();

    bool colorPresent(const Colord& color) const;
    int colorCount(const Colord& color) const;
    unsigned int colorAt(int x, int y) const;
    void show() const;

    std::shared_ptr<raycer::Material> redDiffuse() const;
    void lookAtOrigin();
    void lookAway();
    void goFarAway();
    bool objectVisible() const;
    int objectSize() const;

    int previousObjectSize;

  private:
    raycer::Scene* m_scene;
    std::shared_ptr<raycer::Camera> m_camera;
    std::shared_ptr<raycer::Raycer> m_raycer;
    Buffer<unsigned int> m_buffer;
  };
}

#endif
