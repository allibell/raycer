#pragma once

#include <list>
#include <memory>

#include "raycer/primitives/Primitive.h"

namespace raycer {
  class Composite : public Primitive {
  public:
    typedef std::list<std::shared_ptr<Primitive>> Primitives;

    inline Composite() {}
    
    ~Composite();

    virtual const Primitive* intersect(const Rayd& ray, HitPointInterval& hitPoints, State& state) const;
    virtual bool intersects(const Rayd& ray, State& state) const;

    inline void add(std::shared_ptr<Primitive> primitive) {
      m_primitives.push_back(primitive);
    }

    inline const Primitives& primitives() const {
      return m_primitives;
    }
  
  protected:
    virtual BoundingBoxd calculateBoundingBox() const;

  private:
    Primitives m_primitives;
  };
}
