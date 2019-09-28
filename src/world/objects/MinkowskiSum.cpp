#include "world/objects/ElementFactory.h"
#include "world/objects/MinkowskiSum.h"
#include "raycer/primitives/MinkowskiSum.h"
#include "raycer/primitives/ConvexHull.h"

MinkowskiSum::MinkowskiSum(Element* parent)
  : CSGSurface(parent)
{
}

std::shared_ptr<raycer::Primitive> MinkowskiSum::toRaycerPrimitive() const {
  if (active()) {
    if (children().size() > 0) {
      return make_named<raycer::MinkowskiSum>();
    } else {
      return nullptr;
    }
  } else {
    return make_named<raycer::Composite>();
  }
}

static bool dummy = ElementFactory::self().registerClass<MinkowskiSum>("MinkowskiSum");

#include "MinkowskiSum.moc"
