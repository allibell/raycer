#pragma once

#include "widgets/QtDisplay.h"

class Scene;
class Element;

namespace raycer {
  class Camera;
}

class Display : public QtDisplay {
  Q_OBJECT

  virtual void mousePressEvent(QMouseEvent* event);

public:
  Display(QWidget* parent);
  ~Display();
  
  void setScene(Scene* scene);
};
