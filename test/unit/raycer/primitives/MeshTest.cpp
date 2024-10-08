#include "gtest.h"
#include "core/geometry/Mesh.h"
#include "test/helpers/ContainerTestHelper.h"

#include "raycer/materials/MatteMaterial.h"
#include "raycer/primitives/Scene.h"

namespace MeshTest {
  using namespace ::testing;
  using namespace raycer;
  
  struct MeshTest : public ::testing::Test {
    inline void SetUp() {
      mesh.addVertex(Vector3d(0, 0, 0), Vector3d::null());
      mesh.addVertex(Vector3d(0, 1, 0), Vector3d::null());
      mesh.addVertex(Vector3d(1, 0, 0), Vector3d::null());

      mesh.addFace(makeStdVector(0, 1, 2));
    }
    Mesh mesh;
  };
  
  TEST(Mesh, ShouldInstantiate) {
    Mesh mesh;
  }
  
  TEST_F(MeshTest, ShouldComputeNormals) {
    this->mesh.computeNormals();
    
    ASSERT_EQ(Vector3d(0, 0, 1), mesh.vertices().front().normal);
  }
  
  TEST_F(MeshTest, ShouldAddVertex) {
    auto before = this->mesh.vertices().size();
    this->mesh.addVertex(Vector3d(1, 1, 1), Vector3d::null());
    auto after = this->mesh.vertices().size();
    ASSERT_EQ(1u, after - before);
  }
  
  TEST_F(MeshTest, ShouldAddFace) {
    auto before = this->mesh.faces().size();
    this->mesh.addFace(makeStdVector(2, 1, 0));
    auto after = this->mesh.faces().size();
    ASSERT_EQ(1u, after - before);
  }
  
  TEST_F(MeshTest, ShouldThrowExceptionIfFaceHasLessThanThreeVertices) {
    ASSERT_THROW(this->mesh.addFace(makeStdVector(1)), InvalidMeshFaceException);
  }
  
  TEST_F(MeshTest, ShouldIterateOverEmptyMesh) {
    Mesh mesh;
    int count = 0;
    for (const auto& it : mesh) { (void)it; count++; }
    ASSERT_EQ(0, count);
  }
  
  TEST_F(MeshTest, ShouldIterateOverOneFaceMesh) {
    int count = 0;
    for (const auto& it : this->mesh) { (void)it; count++; }
    ASSERT_EQ(1, count);
  }
  
  TEST_F(MeshTest, ShouldIteratorOverBigMesh) {
    this->mesh.addVertex(Vector3d(1, 1, 1), Vector3d::null());
    this->mesh.addFace(makeStdVector(1, 2, 3, 1, 2));

    int count = 0;
    for (const auto& it : this->mesh) { (void)it; count++; }
    ASSERT_EQ(4, count);
  }
}
