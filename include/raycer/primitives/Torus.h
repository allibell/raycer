#pragma once

#include "raycer/primitives/Primitive.h"
#include "core/math/Vector.h"

namespace raycer {
  class Torus : public Primitive {
  public:
    inline explicit Torus(double sweptRadius, double tubeRadius)
      : m_sweptRadius(sweptRadius),
        m_tubeRadius(tubeRadius)
    {
    }

    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const;

  protected:
    virtual BoundingBoxd calculateBoundingBox() const;

  private:
    Vector3d computeNormal(const Vector3d& p) const;

    double m_sweptRadius;
    double m_tubeRadius;
  };
}
