#pragma once

#include "world/objects/Element.h"
#include "core/math/Vector.h"

namespace raycer {
  class Camera;
}

/**
  * Abstract base class for cameras.
  * 
  * This class defines the few things all camera types have in common: a
  * position in space, and a target the camera looks at.
  */
class Camera : public Element {
  Q_OBJECT
  Q_PROPERTY(Vector3d position READ position WRITE setPosition);
  Q_PROPERTY(Vector3d target READ target WRITE setTarget);
  
public:
  /**
    * Constructor.
    */
  explicit Camera(Element* parent = nullptr);
  
  /**
    * @returns the position of the camera.
    */
  inline const Vector3d& position() const {
    return m_position;
  }
  
  /**
    * Sets the position of the camera.
    * 
    * <table><tr>
    * <td>@image html camera_position_1.png</td>
    * <td>@image html camera_position_2.png</td>
    * <td>@image html camera_position_3.png</td>
    * <td>@image html camera_position_4.png</td>
    * <td>@image html camera_position_5.png</td>
    * </tr></table>
    */
  inline void setPosition(const Vector3d& position) {
    m_position = position;
  }
  
  /**
    * @returns the target of the camera, i.e. the point the camera looks at.
    */
  inline const Vector3d& target() const {
    return m_target;
  }
  
  /**
    * Sets the target point of the camera.
    * 
    * <table><tr>
    * <td>@image html camera_target_1.png</td>
    * <td>@image html camera_target_2.png</td>
    * <td>@image html camera_target_3.png</td>
    * <td>@image html camera_target_4.png</td>
    * <td>@image html camera_target_5.png</td>
    * </tr></table>
    */
  inline void setTarget(const Vector3d& target) {
    m_target = target;
  }
  
  virtual std::shared_ptr<raycer::Camera> toRaycer() const = 0;
  
private:
  Vector3d m_position;
  Vector3d m_target;
};
