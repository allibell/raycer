#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"

#include "raycer/primitives/FlatMeshTriangle.h"
#include "core/geometry/Mesh.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered flat mesh triangle") {
  auto mesh = new Mesh;
  mesh->addVertex(Vector3d(-1, -1, 0), Vector3d(0, 0, 1).normalized());
  mesh->addVertex(Vector3d(-1, 1, 0), Vector3d(0, 0, 1).normalized());
  mesh->addVertex(Vector3d(1, -1, 0), Vector3d(0, 0, 1).normalized());
  
  auto triangle = std::make_shared<FlatMeshTriangle>(mesh, 0, 1, 2);
  triangle->setMaterial(test->redDiffuse());
  test->add(triangle);
}

GIVEN(RaycerFeatureTest, "a displaced flat mesh triangle") {
  auto mesh = new Mesh;
  mesh->addVertex(Vector3d(-1, 20, 0), Vector3d(0, 0, 1).normalized());
  mesh->addVertex(Vector3d(-1, 21, 0), Vector3d(0, 0, 1).normalized());
  mesh->addVertex(Vector3d(1, 20, 0), Vector3d(0, 0, 1).normalized());
  
  auto triangle = std::make_shared<FlatMeshTriangle>(mesh, 0, 1, 2);
  triangle->setMaterial(test->redDiffuse());
  test->add(triangle);
}
