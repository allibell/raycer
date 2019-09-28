#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "core/formats/ply/PlyFile.h"
#include "core/geometry/Mesh.h"
#include "raycer/primitives/Scene.h"
#include "raycer/primitives/Instance.h"
#include "raycer/primitives/FlatMeshTriangle.h"

#include <fstream>

using namespace testing;
using namespace std;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered cube mesh") {
  ifstream stream("test/fixtures/cube.ply");
  auto mesh = new Mesh;
  PlyFile file(stream, *mesh);
  mesh->computeNormals();
  
  FlatMeshTriangle::build(mesh, test->scene(), test->redDiffuse());
}

GIVEN(RaycerFeatureTest, "a displaced cube mesh") {
  ifstream stream("test/fixtures/cube.ply");
  auto mesh = new Mesh;
  PlyFile file(stream, *mesh);
  mesh->computeNormals();
  auto composite = std::make_shared<Composite>();
  FlatMeshTriangle::build(mesh, composite.get(), test->redDiffuse());
  
  auto instance = std::make_shared<Instance>(composite);
  instance->setMatrix(Matrix4d::translate(Vector3d(0, 20, 0)));
  
  test->add(instance);
}

THEN(RaycerFeatureTest, "i should see the mesh") {
  ASSERT_TRUE(test->objectVisible());
}

THEN(RaycerFeatureTest, "i should not see the mesh") {
  ASSERT_FALSE(test->objectVisible());
}
