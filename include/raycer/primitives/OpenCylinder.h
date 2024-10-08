#pragma once

#include "raycer/primitives/Primitive.h"
#include "core/math/Vector.h"

namespace raycer {
  class OpenCylinder : public Primitive {
  public:
    inline explicit OpenCylinder(double radius, double height)
      : m_radius(radius),
        m_halfHeight(height / 2.0),
        m_invRadius(1.0 / radius)
    {
    }

    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const;
    virtual bool intersects(const Rayd& ray, State& state) const;
    virtual Vector3d farthestPoint(const Vector3d& direction) const;

  protected:
    virtual BoundingBoxd calculateBoundingBox() const;

  private:
    double m_radius;
    double m_halfHeight;
    
    double m_invRadius;
  };
}
