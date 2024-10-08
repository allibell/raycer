#pragma once

#include "raycer/primitives/Primitive.h"

class Mesh;

namespace raycer {
  class MeshTriangle : public Primitive {
  public:
    inline explicit MeshTriangle(const Mesh* mesh, int index0, int index1, int index2)
      : Primitive(),
        m_mesh(mesh),
        m_index0(index0),
        m_index1(index1),
        m_index2(index2)
    {
    }
    
  protected:
    virtual BoundingBoxd calculateBoundingBox() const;

  protected:
    const Mesh* m_mesh;
    int m_index0, m_index1, m_index2;
  };
}
