#pragma once

#include <QWidget>
#include <memory>

namespace raycer {
  class Camera;
}

class CameraParameterWidget : public QWidget {
public:
  explicit CameraParameterWidget(QWidget* parent = nullptr);

  virtual void applyTo(std::shared_ptr<raycer::Camera> camera) = 0;
};
