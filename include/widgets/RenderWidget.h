#pragma once

#include <QWidget>
#include <memory>

namespace raycer {
  class Raycer;
}

class RenderWidget : public QWidget {
  Q_OBJECT
public:
  explicit RenderWidget(QWidget* parent, std::shared_ptr<raycer::Raycer> raycer);
  ~RenderWidget();

  virtual void paintEvent(QPaintEvent*);
  virtual void timerEvent(QTimerEvent *event);

  virtual void render();
  void setBufferSize(const QSize& size);
  void setShowProgressIndicators(bool show);

signals:
  void finished();

public slots:
  void stop();

protected:
  std::shared_ptr<raycer::Raycer> m_raycer;

private slots:
  void renderThreadDone();

private:
  void markRectsInProgress(QImage& image) const;
  QRgb darken(QRgb color, double factor) const;

  struct Private;
  std::unique_ptr<Private> p;
};
