#include "world/objects/ElementFactory.h"
#include "world/objects/Intersection.h"
#include "raycer/primitives/Intersection.h"

Intersection::Intersection(Element* parent)
  : CSGSurface(parent)
{
}

std::shared_ptr<raycer::Primitive> Intersection::toRaycerPrimitive() const {
  if (active()) {
    if (children().size() > 0) {
      return make_named<raycer::Intersection>();
    } else {
      return nullptr;
    }
  } else {
    return make_named<raycer::Composite>();
  }
}

static bool dummy = ElementFactory::self().registerClass<Intersection>("Intersection");

#include "Intersection.moc"
