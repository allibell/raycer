#include "world/objects/ElementFactory.h"
#include "world/objects/SphericalCamera.h"

#include "raycer/cameras/SphericalCamera.h"

SphericalCamera::SphericalCamera(Element* parent)
  : Camera(parent),
    m_horizontalFieldOfView(180_degrees),
    m_verticalFieldOfView(120_degrees)
{
}

std::shared_ptr<raycer::Camera> SphericalCamera::toRaycer() const {
  auto camera = make_named<raycer::SphericalCamera>(position(), target());
  camera->setFieldOfView(
    horizontalFieldOfView(),
    verticalFieldOfView()
  );
  return camera;
}

static bool dummy = ElementFactory::self().registerClass<SphericalCamera>("SphericalCamera");

#include "SphericalCamera.moc"

