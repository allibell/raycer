#ifndef ABSTRACT_MESH_TRIANGLE_TEST_H
#define ABSTRACT_MESH_TRIANGLE_TEST_H

#include "core/geometry/Mesh.h"
#include "core/math/Ray.h"
#include "core/math/HitPointInterval.h"
#include "raycer/State.h"

namespace testing {
  using namespace raycer;
  
  template<class MT>
  struct AbstractMeshTriangleTest : public ::testing::Test {
    inline void SetUp() {
      mesh.addVertex(Vector3d(-1, -1, 0), Vector3d(0, 0, 1));
      mesh.addVertex(Vector3d(-1, 1, 0), Vector3d(0, 0, 1));
      mesh.addVertex(Vector3d(1, -1, 0), Vector3d(0, 0, 1));
    }
    
    Mesh mesh;
  };
  
  TYPED_TEST_CASE_P(AbstractMeshTriangleTest);

  TYPED_TEST_P(AbstractMeshTriangleTest, ShouldInitializeWithValues) {
    TypeParam triangle(&this->mesh, 0, 1, 2);
  }
  
  TYPED_TEST_P(AbstractMeshTriangleTest, ShouldIntersectWithRay) {
    TypeParam triangle(&this->mesh, 0, 1, 2);
    Rayd ray(Vector3d(0, 0, -1), Vector3d(0, 0, 1));
    
    State state;
    HitPointInterval hitPoints;
    auto primitive = triangle.intersect(ray, hitPoints, state);
    ASSERT_EQ(primitive, &triangle);
    ASSERT_EQ(Vector3d(0, 0, 0), hitPoints.min().point());
    ASSERT_EQ(Vector3d(0, 0, 1), hitPoints.min().normal());
    ASSERT_EQ(1, hitPoints.min().distance());
    ASSERT_EQ(1, state.intersectionHits);
    ASSERT_EQ(0, state.intersectionMisses);
  }
  
  TYPED_TEST_P(AbstractMeshTriangleTest, ShouldNotIntersectWithMissingRay) {
    TypeParam triangle(&this->mesh, 0, 1, 2);
    Rayd ray(Vector3d(0, 4, -1), Vector3d(0, 0, 1));
    
    State state;
    HitPointInterval hitPoints;
    auto primitive = triangle.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(0, primitive);
    ASSERT_TRUE(hitPoints.min().isUndefined());
    ASSERT_EQ(0, state.intersectionHits);
    ASSERT_EQ(1, state.intersectionMisses);
  }
  
  TYPED_TEST_P(AbstractMeshTriangleTest, ShouldNotIntersectIfPointIsBehindRayOrigin) {
    TypeParam triangle(&this->mesh, 0, 1, 2);
    Rayd ray(Vector3d(0, 0, -1), Vector3d(0, 0, -1));
    
    State state;
    HitPointInterval hitPoints;
    auto primitive = triangle.intersect(ray, hitPoints, state);
    
    ASSERT_EQ(0, primitive);
    ASSERT_TRUE(hitPoints.min().isUndefined());
    ASSERT_EQ(0, state.intersectionHits);
    ASSERT_EQ(1, state.intersectionMisses);
  }
  
  TYPED_TEST_P(AbstractMeshTriangleTest, ShouldReturnTrueForIntersectsIfThereIsAIntersection) {
    TypeParam triangle(&this->mesh, 0, 1, 2);
    Rayd ray(Vector3d(0, 0, -1), Vector3d(0, 0, 1));
    
    State state;
    ASSERT_TRUE(triangle.intersects(ray, state));
  }
  
  TYPED_TEST_P(AbstractMeshTriangleTest, ShouldReturnFalseForIntersectsIfThereIsNoIntersection) {
    TypeParam triangle(&this->mesh, 0, 1, 2);
    Rayd ray(Vector3d(0, 0, -1), Vector3d(0, 0, -1));
    
    State state;
    ASSERT_FALSE(triangle.intersects(ray, state));
  }
  
  REGISTER_TYPED_TEST_CASE_P(
    AbstractMeshTriangleTest,
    ShouldInitializeWithValues,
    ShouldIntersectWithRay,
    ShouldNotIntersectWithMissingRay,
    ShouldNotIntersectIfPointIsBehindRayOrigin,
    ShouldReturnTrueForIntersectsIfThereIsAIntersection,
    ShouldReturnFalseForIntersectsIfThereIsNoIntersection
  );
}

#endif
