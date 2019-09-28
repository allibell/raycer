#pragma once

#include <QWidget>
#include <memory>

class Scene;

class RenderWidget;
class RenderSettingsWidget;

namespace raycer {
  class Raycer;
}

class RenderWindow : public QWidget {
  Q_OBJECT

public:
  explicit RenderWindow(QWidget* parent = nullptr);
  void setScene(::Scene* scene);

  virtual QSize sizeHint() const;
  virtual void timerEvent(QTimerEvent*);
  
  bool isBusy() const;

public slots:
  void render();
  void stop();

private slots:
  void finished();

private:
  struct Private;
  std::unique_ptr<Private> p;
};
