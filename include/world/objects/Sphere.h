#pragma once

#include "world/objects/Surface.h"

/**
  * Represents a sphere primitive.
  * 
  * @image html sphere.png "Sphere with origin (0, 0, 0) and radius 1"
  */
class Sphere : public Surface {
  Q_OBJECT
  Q_PROPERTY(double radius READ radius WRITE setRadius);
  
public:
  /**
    * Default constructor. Creates a sphere with radius 1 around the origin.
    */
  explicit Sphere(Element* parent = nullptr);
  
  /**
    * @returns the radius of the sphere.
    */
  inline double radius() const {
    return m_radius;
  }
  
  /**
    * Sets the radius of the sphere. The radius will be converted to its
    * absolute value. A component of 0 will be replaced with \f$\epsilon\f$.
    * 
    * <table><tr>
    * <td>@image html sphere_size_1.png</td>
    * <td>@image html sphere_size_2.png</td>
    * <td>@image html sphere_size_3.png</td>
    * <td>@image html sphere_size_4.png</td>
    * <td>@image html sphere_size_5.png</td>
    * </tr></table>
    */
  inline void setRadius(double radius) {
    m_radius = std::max(std::abs(radius), std::numeric_limits<double>::epsilon());
  }

  virtual std::shared_ptr<raycer::Primitive> toRaycerPrimitive() const;
  
private:
  double m_radius;
};
