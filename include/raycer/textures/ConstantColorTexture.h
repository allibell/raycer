#include "raycer/textures/Texture.h"
#include "core/Color.h"

namespace raycer {
  class ConstantColorTexture : public Texturec {
  public:
    inline ConstantColorTexture() {}
    
    inline explicit ConstantColorTexture(const Colord& color)
      : m_color(color)
    {
    }
    
    inline const Colord& color() const {
      return m_color;
    }
    
    inline void setColor(const Colord& color) {
      m_color = color;
    }
    
    virtual Colord evaluate(const Rayd& ray, const HitPoint& hitPoint) const;
  
  private:
    Colord m_color;
  };
}
