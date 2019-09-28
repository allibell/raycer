#pragma once

#include "gmock/gmock.h"
#include "raycer/State.h"
#include "raycer/primitives/Primitive.h"
#include "core/math/Ray.h"
#include "core/math/HitPointInterval.h"
#include "test/mocks/MockDestructor.h"

namespace testing {
  class MockPrimitive : public raycer::Primitive, public MockDestructor {
  public:
    MOCK_CONST_METHOD3(intersect, const Primitive*(const Rayd&, HitPointInterval&, raycer::State&));
    MOCK_CONST_METHOD2(intersects, bool(const Rayd&, raycer::State&));
    MOCK_CONST_METHOD1(farthestPoint, Vector3d(const Vector3d&));
    MOCK_CONST_METHOD0(calculateBoundingBox, BoundingBoxd());
    
    inline bool defaultIntersects(const Rayd& ray, raycer::State& state) const {
      return Primitive::intersects(ray, state);
    }

    inline Vector3d defaultFarthestPoint(const Vector3d& direction) const {
      return Primitive::farthestPoint(direction);
    }
  };

  ACTION_P(AddHitPoint, hitPoint) {
    arg1.add(hitPoint);
  }

  ACTION_P2(AddHitPoints, hitPoint1, hitPoint2) {
    arg1.add(hitPoint1, hitPoint2);
  }
}
