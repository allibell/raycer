#include "world/objects/ElementFactory.h"
#include "world/objects/Cylinder.h"
#include "raycer/primitives/ClosedSolidUnion.h"
#include "raycer/primitives/OpenCylinder.h"
#include "raycer/primitives/Disk.h"
#include "raycer/primitives/Torus.h"
#include "raycer/primitives/Instance.h"
#include "raycer/materials/MatteMaterial.h"

Cylinder::Cylinder(Element* parent)
  : Surface(parent),
    m_radius(1),
    m_height(2),
    m_bevelRadius(0)
{
}

std::shared_ptr<raycer::Primitive> Cylinder::toRaycerPrimitive() const {
  auto result = make_named<raycer::ClosedSolidUnion>();

  result->add(make_named<raycer::OpenCylinder>(m_radius, m_height - 2.0 * m_bevelRadius));
  result->add(make_named<raycer::Disk>(
    Vector3d(0, -m_height/2.0, 0), -Vector3d::up(), m_radius - m_bevelRadius
  ));
  result->add(make_named<raycer::Disk>(
    Vector3d(0,  m_height/2.0, 0),  Vector3d::up(), m_radius - m_bevelRadius
  ));

  if (m_bevelRadius > 0.0) {
    for (int sign : { -1, 1 }) {
      auto instance = make_named<raycer::Instance>(
        make_named<raycer::Torus>(m_radius - m_bevelRadius, m_bevelRadius)
      );
      instance->setMatrix(Matrix4d::translate(0, sign * ((m_height / 2.0) - m_bevelRadius), 0));
      result->add(instance);
    }
  }

  return result;
}

static bool dummy = ElementFactory::self().registerClass<Cylinder>("Cylinder");

#include "Cylinder.moc"
