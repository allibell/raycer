#pragma once

#include "widgets/QtDisplay.h"
#include "core/Color.h"

#include <functional>

class Material;
class Scene;
class Camera;

namespace raycer {
  class Scene;
}

class PreviewDisplayWidget : public QtDisplay {
  Q_OBJECT

public:
  explicit PreviewDisplayWidget(QWidget* parent);
  ~PreviewDisplayWidget();
  
  void clear();
  void setMaterial(Material* material, Scene* s);
  void setCamera(Camera* camera, Scene* scene);
  
  virtual QSize sizeHint() const;
  
private:
  void updateScene(const std::function<void()>& setup);
  raycer::Scene* sphereOnPlane(Material* material, Scene* s) const;
};
