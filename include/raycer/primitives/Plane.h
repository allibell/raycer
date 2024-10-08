#pragma once

#include "raycer/primitives/Primitive.h"
#include "core/math/Vector.h"

namespace raycer {
  class Plane : public Primitive {
  public:
    inline explicit Plane(const Vector3d& normal, double distance)
      : m_normal(normal),
        m_distance(distance)
    {
    }

    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const;
    virtual bool intersects(const Rayd& ray, State& state) const;

  protected:
    virtual BoundingBoxd calculateBoundingBox() const;

  private:
    double calculateIntersectionDistance(const Rayd& ray) const;

    Vector3d m_normal;
    double m_distance;
  };
}
