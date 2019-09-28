#include "world/objects/ElementFactory.h"
#include "world/objects/Difference.h"
#include "raycer/primitives/Difference.h"

Difference::Difference(Element* parent)
  : CSGSurface(parent)
{
}

std::shared_ptr<raycer::Primitive> Difference::toRaycerPrimitive() const {
  if (active()) {
    if (children().size() > 0) {
      return make_named<raycer::Difference>();
    } else {
      return nullptr;
    }
  } else {
    return make_named<raycer::Composite>();
  }
}

static bool dummy = ElementFactory::self().registerClass<Difference>("Difference");

#include "Difference.moc"
