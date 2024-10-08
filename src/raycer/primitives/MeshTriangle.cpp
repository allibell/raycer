#include "raycer/primitives/MeshTriangle.h"
#include "core/geometry/Mesh.h"

using namespace raycer;

BoundingBoxd MeshTriangle::calculateBoundingBox() const {
  BoundingBoxd b;
  b.include(m_mesh->vertices()[m_index0].point);
  b.include(m_mesh->vertices()[m_index1].point);
  b.include(m_mesh->vertices()[m_index2].point);
  return b.grownByEpsilon();
}
