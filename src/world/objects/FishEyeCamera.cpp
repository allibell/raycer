#include "world/objects/ElementFactory.h"
#include "world/objects/FishEyeCamera.h"

#include "raycer/cameras/FishEyeCamera.h"

FishEyeCamera::FishEyeCamera(Element* parent)
  : Camera(parent),
    m_fieldOfView(180_degrees)
{
}

std::shared_ptr<raycer::Camera> FishEyeCamera::toRaycer() const {
  auto camera = make_named<raycer::FishEyeCamera>(position(), target());
  camera->setFieldOfView(fieldOfView());
  return camera;
}

static bool dummy = ElementFactory::self().registerClass<FishEyeCamera>("FishEyeCamera");

#include "FishEyeCamera.moc"
