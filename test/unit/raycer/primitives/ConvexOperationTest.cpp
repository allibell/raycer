#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "raycer/State.h"
#include "raycer/primitives/ConvexOperation.h"
#include "raycer/materials/MatteMaterial.h"
#include "test/mocks/raycer/MockPrimitive.h"

namespace testing {
  class MockConvexOperation : public raycer::ConvexOperation {
  public:
    Vector3d farthestPoint(const Vector3d& direction) const {
      return direction.x() < 0 ? Vector3d(-2, 0, 0) : Vector3d(2, 0, 0);
    }
  };
}

namespace ConvexOperationTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(ConvexOperation, ShouldReturnSelfForConvexOperation) {
    MockConvexOperation i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd( Vector3d::one(), Vector3d::one())));
    
    Rayd ray(Vector3d(-5, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    HitPointInterval hitPoints;
    auto result = i.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(Vector3d(-2, 0, 0), hitPoints.min().point());
    ASSERT_EQ(Vector3d( 2, 0, 0), hitPoints.max().point());
    ASSERT_EQ(&i, result);
  }

  TEST(ConvexOperation, ShouldNotReturnAnyPrimitiveRayOutsideBoundingBox) {
    MockConvexOperation i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd::undefined()));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    HitPointInterval hitPoints;
    auto result = i.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(nullptr, result);
  }

  TEST(ConvexOperation, ShouldIntersectIfRayHits) {
    MockConvexOperation i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd( Vector3d::one(), Vector3d::one())));
    
    Rayd ray(Vector3d(-5, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    ASSERT_TRUE(i.intersects(ray, state));
  }

  TEST(ConvexOperation, ShouldNotIntersectIfRayOutsideBoundingBox) {
    MockConvexOperation i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd::undefined()));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    ASSERT_FALSE(i.intersects(ray, state));
  }
}
