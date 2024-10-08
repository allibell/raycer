#pragma once

#include "raycer/primitives/Primitive.h"
#include "core/math/Vector.h"

namespace raycer {
  class Triangle : public Primitive {
  public:
    inline explicit Triangle(const Vector3d& a, const Vector3d& b, const Vector3d& c)
      : Primitive(),
        m_point0(a),
        m_point1(b),
        m_point2(c)
    {
      m_normal = computeNormal();
    }

    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const;

  protected:
    virtual BoundingBoxd calculateBoundingBox() const;

  private:
    Vector3d computeNormal() const;

    Vector3d m_point0, m_point1, m_point2;
    Vector3d m_normal;
  };
}
