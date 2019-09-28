#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "raycer/State.h"
#include "raycer/primitives/Primitive.h"
#include "core/math/Ray.h"
#include "test/mocks/raycer/MockPrimitive.h"

namespace PrimitiveTest {
  using namespace raycer;
  using namespace testing;

  TEST(Primitive, ShouldReturnTrueForIntersectsIfIntersectReturnsObject) {
    auto primitive = std::make_shared<NiceMock<MockPrimitive>>();
    ON_CALL(*primitive, intersects(_, _)).WillByDefault(Invoke(primitive.get(), &NiceMock<MockPrimitive>::defaultIntersects));
    EXPECT_CALL(*primitive, intersect(_, _, _)).WillOnce(
      DoAll(
        AddHitPoint(HitPoint(primitive.get(), 1.0, Vector3d(), Vector3d(1, 0, 0))),
        Return(primitive.get())
      )
    );
    
    State state;
    ASSERT_TRUE(primitive->intersects(Rayd(Vector3d::null(), Vector3d::one()), state));
  }

  TEST(Primitive, ShouldReturnTrueForIntersectsIfIntersectReturnsNoObject) {
    auto primitive = std::make_shared<NiceMock<MockPrimitive>>();
    ON_CALL(*primitive, intersects(_, _)).WillByDefault(Invoke(primitive.get(), &NiceMock<MockPrimitive>::defaultIntersects));
    EXPECT_CALL(*primitive, intersect(_, _, _)).WillOnce(Return(nullptr));
    
    State state;
    ASSERT_FALSE(primitive->intersects(Rayd(Vector3d::null(), Vector3d::one()), state));
  }
  
  TEST(Primitive, ShouldReturnFarthestPoint) {
    auto primitive = std::make_shared<NiceMock<MockPrimitive>>();
    ON_CALL(*primitive, farthestPoint(_)).WillByDefault(Invoke(primitive.get(), &NiceMock<MockPrimitive>::defaultFarthestPoint));
    
    ASSERT_TRUE(primitive->farthestPoint(Vector3d::up()).isUndefined());
  }
}
