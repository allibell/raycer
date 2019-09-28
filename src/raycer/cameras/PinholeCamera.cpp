#include "raycer/cameras/CameraFactory.h"
#include "raycer/cameras/PinholeCamera.h"
#include "core/math/Ray.h"
#include "raycer/viewplanes/ViewPlane.h"

using namespace raycer;

Rayd PinholeCamera::rayForPixel(double x, double y) const {
  Vector3d position = matrix() * Vector4d(0, 0, -m_distance);
  Vector3d pixel = viewPlane()->pixelAt(x, y);
  return Rayd(position, (pixel - position).normalized());
}

void PinholeCamera::setViewPlane(std::shared_ptr<ViewPlane> plane) {
  Camera::setViewPlane(plane);
  viewPlane()->setPixelSize(1.0 / m_zoom);
}

static bool dummy = CameraFactory::self().registerClass<PinholeCamera>("PinholeCamera");
