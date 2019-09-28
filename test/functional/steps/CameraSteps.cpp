#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/cameras/PinholeCamera.h"
#include "raycer/cameras/OrthographicCamera.h"

using namespace testing;

WHEN(RaycerFeatureTest, "i look at the origin") {
  test->lookAtOrigin();
}

WHEN(RaycerFeatureTest, "i look away from the origin") {
  test->lookAway();
}

WHEN(RaycerFeatureTest, "i go far away from the origin") {
  test->goFarAway();
}

WHEN(RaycerFeatureTest, "i zoom in") {
  auto camera = static_cast<raycer::Camera*>(test->camera().get());
  if (auto c = dynamic_cast<raycer::PinholeCamera*>(camera)) {
    c->setZoom(c->zoom() * 2);
  } else if (auto c = dynamic_cast<raycer::OrthographicCamera*>(camera)) {
    c->setZoom(c->zoom() * 2);
  }
}

WHEN(RaycerFeatureTest, "i zoom out") {
  auto camera = static_cast<raycer::Camera*>(test->camera().get());
  if (auto c = dynamic_cast<raycer::PinholeCamera*>(camera)) {
    c->setZoom(c->zoom() * 0.8);
  } else if (auto c = dynamic_cast<raycer::OrthographicCamera*>(camera)) {
    c->setZoom(c->zoom() * 0.8);
  }
}
