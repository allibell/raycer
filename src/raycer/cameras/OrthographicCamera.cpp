#include "raycer/cameras/CameraFactory.h"
#include "raycer/cameras/OrthographicCamera.h"
#include "core/math/Ray.h"
#include "raycer/viewplanes/ViewPlane.h"

using namespace raycer;

Rayd OrthographicCamera::rayForPixel(double x, double y) const {
  Vector3d direction = Matrix3d(matrix()) * Vector3d::forward();
  Vector3d pixel = viewPlane()->pixelAt(x, y);
  return Rayd(pixel, direction);
}

void OrthographicCamera::setViewPlane(std::shared_ptr<ViewPlane> plane) {
  Camera::setViewPlane(plane);
  viewPlane()->setPixelSize(1.0 / m_zoom);
}

static bool dummy = CameraFactory::self().registerClass<OrthographicCamera>("OrthographicCamera");
