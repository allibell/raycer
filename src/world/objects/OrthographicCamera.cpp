#include "world/objects/ElementFactory.h"
#include "world/objects/OrthographicCamera.h"

#include "raycer/cameras/OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(Element* parent)
  : Camera(parent),
    m_zoom(1)
{
}

std::shared_ptr<raycer::Camera> OrthographicCamera::toRaycer() const {
  auto camera = make_named<raycer::OrthographicCamera>(position(), target());
  camera->setZoom(zoom());
  return camera;
}

static bool dummy = ElementFactory::self().registerClass<OrthographicCamera>("OrthographicCamera");

#include "OrthographicCamera.moc"
