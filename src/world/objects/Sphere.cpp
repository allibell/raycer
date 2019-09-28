#include "world/objects/ElementFactory.h"
#include "world/objects/Sphere.h"
#include "raycer/primitives/Sphere.h"
#include "raycer/materials/MatteMaterial.h"

Sphere::Sphere(Element* parent)
  : Surface(parent),
    m_radius(1)
{
}

std::shared_ptr<raycer::Primitive> Sphere::toRaycerPrimitive() const {
  return make_named<raycer::Sphere>(Vector3d::null(), m_radius);
}

static bool dummy = ElementFactory::self().registerClass<Sphere>("Sphere");

#include "Sphere.moc"
