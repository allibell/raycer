#include "gtest.h"
#include "test/helpers/ContainerTestHelper.h"
#include "test/abstract/AbstractMeshTriangleTest.h"

#include "raycer/primitives/SmoothMeshTriangle.h"
#include "raycer/primitives/Composite.h"

namespace SmoothMeshTriangleTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(SmoothMeshTriangle, ShouldBuildFromMesh) {
    Mesh mesh;
    mesh.addVertex(Vector3d(-1, -1, 0), Vector3d(0, -2, 1).normalized());
    mesh.addVertex(Vector3d(-1, 1, 0), Vector3d(-2, 0, 1).normalized());
    mesh.addVertex(Vector3d(1, -1, 0), Vector3d(0, 2, 1).normalized());
    mesh.addFace(makeStdVector(0, 1, 2));
    
    auto composite = new Composite;
    SmoothMeshTriangle::build(&mesh, composite, nullptr);
    ASSERT_EQ(1u, composite->primitives().size());
  }
  
  TEST(SmoothMeshTriangle, ShouldHaveDifferentNormalsAtDifferentHitPoints) {
    Mesh mesh;
    mesh.addVertex(Vector3d(-1, -1, 0), Vector3d(0, -2, 1).normalized());
    mesh.addVertex(Vector3d(-1, 1, 0), Vector3d(-2, 0, 1).normalized());
    mesh.addVertex(Vector3d(1, -1, 0), Vector3d(0, 2, 1).normalized());
    
    State state;
    SmoothMeshTriangle triangle(&mesh, 0, 1, 2);
    HitPointInterval hitPoints1;
    Rayd ray1(Vector3d(0, 0, -1), Vector3d(0, 0, 1));
    triangle.intersect(ray1, hitPoints1, state);
    Vector3d normal1 = hitPoints1.min().normal();

    HitPointInterval hitPoints2;
    Rayd ray2(Vector3d(-1, -1, -1), Vector3d(0, 0, 1));
    triangle.intersect(ray2, hitPoints2, state);
    Vector3d normal2 = hitPoints2.min().normal();
    
    ASSERT_NE(normal1, normal2);
  }

  INSTANTIATE_TYPED_TEST_CASE_P(
    Smooth,
    AbstractMeshTriangleTest,
    SmoothMeshTriangle
  );
}
