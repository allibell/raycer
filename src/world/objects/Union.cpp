#include "world/objects/ElementFactory.h"
#include "world/objects/Union.h"
#include "raycer/primitives/Union.h"

Union::Union(Element* parent)
  : CSGSurface(parent)
{
}

std::shared_ptr<raycer::Primitive> Union::toRaycerPrimitive() const {
  if (active()) {
    if (children().size() > 0) {
      return make_named<raycer::Union>();
    } else {
      return nullptr;
    }
  } else {
    return make_named<raycer::Composite>();
  }
}

static bool dummy = ElementFactory::self().registerClass<Union>("Union");

#include "Union.moc"
