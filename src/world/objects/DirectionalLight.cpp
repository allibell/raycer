#include "world/objects/ElementFactory.h"
#include "world/objects/DirectionalLight.h"
#include "raycer/lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(Element* parent)
  : Light(parent),
    m_direction(-0.5, -1, -0.5)
{
}

std::shared_ptr<raycer::Light> DirectionalLight::toRaycer() const {
  return make_named<raycer::DirectionalLight>(Matrix3d(globalTransform()) * direction(), color() * intensity());
}

static bool dummy = ElementFactory::self().registerClass<DirectionalLight>("DirectionalLight");

#include "DirectionalLight.moc"
