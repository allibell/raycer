#include "world/objects/ElementFactory.h"
#include "world/objects/PinholeCamera.h"

#include "raycer/cameras/PinholeCamera.h"

PinholeCamera::PinholeCamera(Element* parent)
  : Camera(parent),
    m_distance(5),
    m_zoom(1)
{
}

std::shared_ptr<raycer::Camera> PinholeCamera::toRaycer() const {
  auto camera = make_named<raycer::PinholeCamera>(position(), target());
  camera->setDistance(distance());
  camera->setZoom(zoom());
  return camera;
}

static bool dummy = ElementFactory::self().registerClass<PinholeCamera>("PinholeCamera");

#include "PinholeCamera.moc"
