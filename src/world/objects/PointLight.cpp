#include "world/objects/ElementFactory.h"
#include "world/objects/PointLight.h"
#include "raycer/lights/PointLight.h"

PointLight::PointLight(Element* parent)
  : Light(parent)
{
}

std::shared_ptr<raycer::Light> PointLight::toRaycer() const {
  return make_named<raycer::PointLight>(globalTransform() * Vector3d::null(), color() * intensity());
}

static bool dummy = ElementFactory::self().registerClass<PointLight>("PointLight");

#include "PointLight.moc"
