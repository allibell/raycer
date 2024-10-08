#pragma once

#include "raycer/brdf/BRDF.h"
#include "core/math/Range.h"

namespace raycer {
  class Lambertian : public BRDF {
  public:
    inline Lambertian()
      : m_reflectionCoefficient(1)
    {
    }
    
    inline explicit Lambertian(const Colord& color, double coeff)
      : m_diffuseColor(color),
        m_reflectionCoefficient(coeff)
    {
    }
    
    virtual Colord calculate(const HitPoint& hitPoint, const Vector3d& out, const Vector3d& in) const;
    virtual Colord reflectance(const HitPoint& hitPoint, const Vector3d& out) const;
    
    inline const Colord& diffuseColor() const {
      return m_diffuseColor;
    }
    
    inline void setDiffuseColor(const Colord& color) {
      m_diffuseColor = color;
    }
    
    inline double reflectionCoefficient() const {
      return m_reflectionCoefficient;
    }
    
    inline void setReflectionCoefficient(double coeff) {
      m_reflectionCoefficient = Ranged(0, 1).clamp(coeff);
    }
    
  private:
    Colord m_diffuseColor;
    double m_reflectionCoefficient;
  };
}
