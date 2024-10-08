#pragma once

#include "core/math/Angle.h"
#include "raycer/cameras/Camera.h"

namespace raycer {
  class ViewPlane;

  /**
    * Fish eye cameras produce a hemispherical projection of the scene onto the
    * view plane.
    * 
    * @image html fish_eye_camera_cube.png "Fish eye with fieldOfView=180°"
    */
  class FishEyeCamera : public Camera {
  public:
    /**
      * Creates a default fish eye camera with a 120 degree field of view,
      * looking at the origin.
      */
    inline explicit FishEyeCamera()
      : m_fieldOfView(120_degrees)
    {
    }
    
    /**
      * Creates a fish eye camera with the given field of view, looking at the
      * origin.
      */
    inline explicit FishEyeCamera(const Angled& fieldOfView)
      : m_fieldOfView(fieldOfView)
    {
    }
    
    /**
      * Creates a fish eye camera at position looking at target.
      */
    inline explicit FishEyeCamera(const Vector3d& position, const Vector3d& target)
      : Camera(position, target),
        m_fieldOfView(120_degrees)
    {
    }

    virtual Rayd rayForPixel(double x, double y) const;

    /**
      * @returns the camera's field of view.
      */
    inline Angled fieldOfView() const {
      return m_fieldOfView;
    }
    
    /**
      * Sets the field of view of the camera.
      * 
      * <table><tr>
      * <td>@image html fish_eye_camera_cube_fov_90.png "fieldOfView=90"</td>
      * <td>@image html fish_eye_camera_cube_fov_150.png "fieldOfView=150"</td>
      * <td>@image html fish_eye_camera_cube_fov_210.png "fieldOfView=210"</td>
      * <td>@image html fish_eye_camera_cube_fov_270.png "fieldOfView=270"</td>
      * <td>@image html fish_eye_camera_cube_fov_330.png "fieldOfView=330"</td>
      * </tr></table>
      */
    inline void setFieldOfView(const Angled& fieldOfView) {
      m_fieldOfView = fieldOfView;
    }
    
  private:
    Vector3d direction(double x, double y) const;
    Angled m_fieldOfView;
  };
}
