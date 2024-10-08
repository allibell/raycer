#include "raycer/State.h"
#include "raycer/primitives/Intersection.h"
#include "core/math/HitPointInterval.h"
#include "core/math/Ray.h"

using namespace raycer;

const Primitive* Intersection::intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const {
  if (!boundingBoxIntersects(ray)) {
    return nullptr;
  }

  unsigned int numHits = 0;
  for (const auto& i : primitives()) {
    HitPointInterval candidate;
    if (i->intersect(ray, candidate, state)) {
      if (numHits) {
        hitPoints = hitPoints & candidate;
      } else {
        hitPoints = candidate;
      }
      numHits++;
    }
  }
  
  if (numHits != primitives().size() || hitPoints.empty()) {
    return nullptr;
  } else {
    if (material()) {
      hitPoints.setPrimitive(this);
      return this;
    } else {
      return hitPoints.minWithPositiveDistance().primitive();
    }
  }
}

bool Intersection::intersects(const Rayd& ray, State& state) const {
  if (!boundingBoxIntersects(ray)) {
    return false;
  }

  for (const auto& i : primitives()) {
    if (!i->intersects(ray, state))
      return false;
  }
  
  return true;
}

BoundingBoxd Intersection::calculateBoundingBox() const {
  BoundingBoxd result;
  int num = 0;
  for (const auto& i : primitives()) {
    if (num++ == 0)
      result = i->boundingBox();
    else
      result &= i->boundingBox();
  }
  return result;
}
