#pragma once

#include "core/math/BoundingBox.h"
#include "core/math/Ray.h"
#include "core/MemoizedValue.h"

#include "raycer/Object.h"

#include <memory>


class HitPointInterval;

namespace raycer {
  class Material;
  class State;

  class Primitive : public Object {
  public:
    inline Primitive()
      : m_material(nullptr)
    {
    }
    virtual ~Primitive() {}

    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const = 0;
    virtual bool intersects(const Rayd& ray, State& state) const;

    inline const BoundingBoxd& boundingBox() const {
      if (!m_cachedBoundingBox) {
        m_cachedBoundingBox = calculateBoundingBox();
      }

      return m_cachedBoundingBox.value();
    }

    inline void setMaterial(std::shared_ptr<Material> material) {
      m_material = material;
    }

    inline virtual std::shared_ptr<Material> material() const {
      return m_material;
    }

    virtual Vector3d farthestPoint(const Vector3d& direction) const;

  protected:
    virtual BoundingBoxd calculateBoundingBox() const = 0;

    inline bool boundingBoxIntersects(const Rayd& ray) const {
      return boundingBox().intersects(ray);
    }

    bool convexIntersect(const Rayd& ray, HitPointInterval& hitPoints) const;

  private:
    std::shared_ptr<Material> m_material;
    mutable MemoizedValue<BoundingBoxd> m_cachedBoundingBox;
  };
}
