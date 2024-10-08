#pragma once

#include "widgets/QtDisplay.h"

class QVBoxLayout;
class SceneWidget;
class ViewPlaneTypeWidget;
class CameraTypeWidget;
class CameraParameterWidget;

namespace raycer {
  class Camera;
}

class Display : public QtDisplay {
  Q_OBJECT

public:
  Display();
  ~Display();
  
  virtual void mousePressEvent(QMouseEvent* event);

private slots:
  void sceneChanged();
  void viewPlaneTypeChanged();
  void cameraTypeChanged();
  void cameraParameterChanged();

private:
  QVBoxLayout* m_verticalLayout;
  std::shared_ptr<raycer::Camera> m_camera;
  QWidget* m_sidebar;
  SceneWidget* m_scene;
  ViewPlaneTypeWidget* m_viewPlaneType;
  CameraTypeWidget* m_cameraType;
  CameraParameterWidget* m_cameraParameter;
};
