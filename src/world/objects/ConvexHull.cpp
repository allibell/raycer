#include "world/objects/ElementFactory.h"
#include "world/objects/ConvexHull.h"
#include "raycer/primitives/ConvexHull.h"
#include "raycer/primitives/ConvexHull.h"

ConvexHull::ConvexHull(Element* parent)
  : CSGSurface(parent)
{
}

std::shared_ptr<raycer::Primitive> ConvexHull::toRaycerPrimitive() const {
  if (active()) {
    if (children().size() > 0) {
      return make_named<raycer::ConvexHull>();
    } else {
      return nullptr;
    }
  } else {
    return make_named<raycer::Composite>();
  }
}

static bool dummy = ElementFactory::self().registerClass<ConvexHull>("ConvexHull");

#include "ConvexHull.moc"
