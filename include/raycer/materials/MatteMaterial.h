#pragma once

#include <memory>

#include "raycer/materials/Material.h"
#include "raycer/brdf/Lambertian.h"
#include "raycer/textures/Texture.h"

namespace raycer {
  /**
    * Matte materials have no reflection, or transmission. As the name suggests,
    * they appear matte.
    * 
    * @image html matte_material_red.png "Matte material with red constant texture"
    */
  class MatteMaterial : public Material {
  public:
    /**
      * Constructs the default matte material with no texture and ambient and
      * diffuse coefficients of 1.
      */
    inline MatteMaterial()
      : Material(),
        m_diffuseTexture(nullptr),
        m_ambientCoefficient(1),
        m_diffuseCoefficient(1)
    {
    }

    /**
      * Constructs the default matte material with the given texture and ambient
      * and diffuse coefficients of 1.
      */
    inline explicit MatteMaterial(std::shared_ptr<Texturec> texture)
      : Material(),
        m_diffuseTexture(texture),
        m_ambientCoefficient(1),
        m_diffuseCoefficient(1)
    {
    }

    /**
      * @returns the diffuse texture.
      */
    inline std::shared_ptr<Texturec> diffuseTexture() const {
      return m_diffuseTexture;
    }

    /**
      * Sets the material's diffuse texture.
      * 
      * <table><tr>
      * <td>@image html matte_material_rainbow_red.png</td>
      * <td>@image html matte_material_rainbow_orange.png</td>
      * <td>@image html matte_material_rainbow_yellow.png</td>
      * <td>@image html matte_material_rainbow_green.png</td>
      * <td>@image html matte_material_rainbow_blue.png</td>
      * <td>@image html matte_material_rainbow_indigo.png</td>
      * <td>@image html matte_material_rainbow_violet.png</td>
      * </tr></table>
      */
    inline void setDiffuseTexture(std::shared_ptr<Texturec> texture) {
      m_diffuseTexture = texture;
    }
    
    /**
      * @returns the ambient light coefficient.
      */
    inline double ambientCoefficient() const {
      return m_ambientCoefficient;
    }
  
    /**
      * Sets the ambient light coefficient.
      * 
      * <table><tr>
      * <td>@image html matte_material_ambient_0.0.png "ambientCoefficient=0"</td>
      * <td>@image html matte_material_ambient_0.25.png "ambientCoefficient=0.25"</td>
      * <td>@image html matte_material_ambient_0.5.png "ambientCoefficient=0.5"</td>
      * <td>@image html matte_material_ambient_0.75.png "ambientCoefficient=0.75"</td>
      * <td>@image html matte_material_ambient_1.0.png "ambientCoefficient=1"</td>
      * </tr></table>
      */
    inline void setAmbientCoefficient(double coeff) {
      m_ambientCoefficient = coeff;
    }
    
    /**
      * @returns the diffuse light coefficient.
      */
    inline double diffuseCoefficient() const {
      return m_diffuseCoefficient;
    }
  
    /**
      * Sets the diffuse light coefficient.
      * 
      * <table><tr>
      * <td>@image html matte_material_diffuse_0.0.png "diffuseCoefficient=0"</td>
      * <td>@image html matte_material_diffuse_0.5.png "diffuseCoefficient=0.5"</td>
      * <td>@image html matte_material_diffuse_1.0.png "diffuseCoefficient=1"</td>
      * <td>@image html matte_material_diffuse_1.5.png "diffuseCoefficient=1.5"</td>
      * <td>@image html matte_material_diffuse_2.0.png "diffuseCoefficient=2"</td>
      * </tr></table>
      */
    inline void setDiffuseCoefficient(double coeff) {
      m_diffuseCoefficient = coeff;
    }
    
    virtual Colord shade(const Raycer* raycer, const Rayd& ray, const HitPoint& hitPoint, State& state) const;

  private:
    std::shared_ptr<Texturec> m_diffuseTexture;
    double m_ambientCoefficient;
    double m_diffuseCoefficient;
  };
}
