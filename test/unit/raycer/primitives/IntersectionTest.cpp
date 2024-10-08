#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "raycer/State.h"
#include "raycer/primitives/Intersection.h"
#include "raycer/materials/MatteMaterial.h"
#include "test/mocks/raycer/MockPrimitive.h"

namespace IntersectionTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(Intersection, ShouldReturnClosestPrimitiveForIntersection) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive1, intersect(_, _, _)).WillOnce(
      DoAll(
        AddHitPoints(
          HitPoint(primitive1.get(), 1.0, Vector3d(), Vector3d()),
          HitPoint(primitive1.get(), 4.0, Vector3d(), Vector3d())
        ),
        Return(primitive1.get())
      )
    );
    EXPECT_CALL(*primitive2, intersect(_, _, _)).WillOnce(
      DoAll(
        AddHitPoints(
          HitPoint(primitive2.get(), 2.0, Vector3d(), Vector3d()),
          HitPoint(primitive2.get(), 5.0, Vector3d(), Vector3d())
        ),
        Return(primitive2.get())
      )
    );
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    HitPointInterval hitPoints;
    auto result = i.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(primitive2.get(), result);
  }

  TEST(Intersection, ShouldReturnSelfIfIntersectionHasMaterial) {
    Intersection i;
    i.setMaterial(std::make_shared<MatteMaterial>());
    
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive1, intersect(_, _, _)).WillOnce(
      DoAll(
        AddHitPoints(
          HitPoint(primitive1.get(), 1.0, Vector3d(), Vector3d()),
          HitPoint(primitive1.get(), 4.0, Vector3d(), Vector3d())
        ),
        Return(primitive1.get())
      )
    );
    EXPECT_CALL(*primitive2, intersect(_, _, _)).WillOnce(
      DoAll(
        AddHitPoints(
          HitPoint(primitive2.get(), 2.0, Vector3d(), Vector3d()),
          HitPoint(primitive2.get(), 5.0, Vector3d(), Vector3d())
        ),
        Return(primitive2.get())
      )
    );
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    HitPointInterval hitPoints;
    auto result = i.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(&i, result);
  }
  
  TEST(Intersection, ShouldNotReturnAnyPrimitiveIfThereIsNoIntersection) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive1, intersect(_, _, _)).WillOnce(Return(static_cast<Primitive*>(nullptr)));
    EXPECT_CALL(*primitive2, intersect(_, _, _)).WillOnce(Return(static_cast<Primitive*>(nullptr)));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    HitPointInterval hitPoints;
    auto result = i.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(0, result);
  }
  
  TEST(Intersection, ShouldNotReturnAnyPrimitiveIfNotAllChildrenIntersect) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive1, intersect(_, _, _)).WillOnce(
      DoAll(
        AddHitPoints(
          HitPoint(primitive1.get(), 1.0, Vector3d(), Vector3d()),
          HitPoint(primitive1.get(), 4.0, Vector3d(), Vector3d())
        ),
        Return(primitive1.get())
      )
    );
    EXPECT_CALL(*primitive2, intersect(_, _, _)).WillOnce(Return(static_cast<Primitive*>(nullptr)));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    HitPointInterval hitPoints;
    auto result = i.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(0, result);
  }
  
  TEST(Intersection, ShouldNotReturnAnyPrimitiveIfNotAllChildrenIntersectInOverlappingIntervals) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive1.get(), intersect(_, _, _)).WillOnce(
      DoAll(
        AddHitPoints(
          HitPoint(primitive1.get(), 1.0, Vector3d(), Vector3d()),
          HitPoint(primitive1.get(), 2.0, Vector3d(), Vector3d())
        ),
        Return(primitive1.get())
      )
    );
    EXPECT_CALL(*primitive2.get(), intersect(_, _, _)).WillOnce(
      DoAll(
        AddHitPoints(
          HitPoint(primitive2.get(), 3.0, Vector3d(), Vector3d()),
          HitPoint(primitive2.get(), 4.0, Vector3d(), Vector3d())
        ),
        Return(primitive2.get())
      )
    );
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    HitPointInterval hitPoints;
    auto result = i.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(0, result);
  }

  TEST(Intersection, ShouldNotReturnAnyPrimitiveIfRayOutsideOfBoundingBox) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd::undefined()));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd::undefined()));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    HitPointInterval hitPoints;
    auto result = i.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(0, result);
  }
  
  TEST(Intersection, ShouldReturnTrueForIntersectsIfAllOfTheChildPrimitivesIntersect) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive1, intersects(_, _)).WillOnce(Return(true));
    EXPECT_CALL(*primitive2, intersects(_, _)).WillOnce(Return(true));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    bool result = i.intersects(ray, state);
    
    ASSERT_TRUE(result);
  }
  
  TEST(Intersection, ShouldReturnFalseForIntersectsIfThereIsNoIntersection) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive1, intersects(_, _)).WillOnce(Return(false));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    bool result = i.intersects(ray, state);
    
    ASSERT_FALSE(result);
  }
  
  TEST(Intersection, ShouldReturnFalseForIntersectsIfNotAllChildrenIntersect) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(-Vector3d::one(), Vector3d::one())));
    EXPECT_CALL(*primitive1, intersects(_, _)).WillOnce(Return(true));
    EXPECT_CALL(*primitive2, intersects(_, _)).WillOnce(Return(false));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    bool result = i.intersects(ray, state);
    
    ASSERT_FALSE(result);
  }
  
  TEST(Intersection, ShouldReturnFalseForIntersectsIfRayOutsideBoundingBox) {
    Intersection i;
    auto primitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto primitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(primitive1);
    i.add(primitive2);
    EXPECT_CALL(*primitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd::undefined()));
    EXPECT_CALL(*primitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd::undefined()));
    
    Rayd ray(Vector3d(0, 0, 0), Vector3d(1, 0, 0));
    
    State state;
    bool result = i.intersects(ray, state);
    
    ASSERT_FALSE(result);
  }
  
  TEST(Intersection, ShouldReturnBoundingBoxWithOneChild) {
    Intersection i;
    auto mockPrimitive = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(mockPrimitive);
    
    BoundingBoxd bbox(Vector3d(-1, -1, -1), Vector3d(1, 1, 1));
    EXPECT_CALL(*mockPrimitive, calculateBoundingBox()).WillOnce(Return(bbox));
    
    ASSERT_EQ(bbox, i.boundingBox());
  }
  
  TEST(Intersection, ShouldReturnBoundingBoxWithMultipleChildren) {
    Intersection i;
    auto mockPrimitive1 = std::make_shared<NiceMock<MockPrimitive>>();
    auto mockPrimitive2 = std::make_shared<NiceMock<MockPrimitive>>();
    i.add(mockPrimitive1);
    i.add(mockPrimitive2);
    
    EXPECT_CALL(*mockPrimitive1, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(Vector3d(-1, -1, -1), Vector3d(1, 1, 1))));
    EXPECT_CALL(*mockPrimitive2, calculateBoundingBox()).WillOnce(Return(BoundingBoxd(Vector3d(0, 0, 0), Vector3d(2, 2, 2))));
    
    BoundingBoxd expected(Vector3d(0, 0, 0), Vector3d(1, 1, 1));
    ASSERT_EQ(expected, i.boundingBox());
  }
}
