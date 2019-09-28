#pragma once

#include "widgets/RenderWidget.h"

namespace raycer {
  class Raycer;
}

class QtDisplay : public RenderWidget {
  Q_OBJECT
public:
  explicit QtDisplay(QWidget* parent, std::shared_ptr<raycer::Raycer> raycer);
  ~QtDisplay();
  
  void setInteractive(bool interactive);
  bool interactive() const;
  
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void wheelEvent(QWheelEvent* event);
  virtual void resizeEvent(QResizeEvent* event);

  virtual void render();
  
  void setDistance(double distance);

private:
  struct Private;
  std::unique_ptr<Private> p;
};
