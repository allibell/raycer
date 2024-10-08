#include "raycer/samplers/SamplerFactory.h"
#include "raycer/viewplanes/ViewPlaneFactory.h"
#include "widgets/world/RenderSettingsWidget.h"
#include "RenderSettingsWidget.uic"

#include <QThread>

struct RenderSettingsWidget::Private {
  Ui::RenderSettingsWidget ui;
};

RenderSettingsWidget::RenderSettingsWidget(QWidget* parent)
  : QWidget(parent),
    p(std::make_unique<Private>())
{
  p->ui.setupUi(this);

  auto ids = raycer::SamplerFactory::self().identifiers();
  for (const auto& id : ids) {
    p->ui.samplerType->addItem(QString(id.c_str()).replace("Sampler", ""));
  }

  p->ui.samplerType->setCurrentText("Regular");

  ids = raycer::ViewPlaneFactory::self().identifiers();
  for (const auto& id : ids) {
    p->ui.viewPlaneType->addItem(QString(id.c_str()));
  }

  p->ui.viewPlaneType->setCurrentText("PointInterlacedViewPlane");

  p->ui.renderThreads->setValue(QThread::idealThreadCount());
  p->ui.queueSize->setValue(QThread::idealThreadCount() * 8);

  connect(p->ui.renderButton, SIGNAL(clicked()), this, SLOT(render()));
  connect(p->ui.stopButton, SIGNAL(clicked()), this, SLOT(stop()));
}

RenderSettingsWidget::~RenderSettingsWidget() {
}

QSize RenderSettingsWidget::resolution() const {
  QString resolution = p->ui.resolution->currentText();
  auto components = resolution.split("x");

  return QSize(components[0].toInt(), components[1].toInt());
}

QString RenderSettingsWidget::sampler() const {
  return p->ui.samplerType->currentText();
}

QString RenderSettingsWidget::viewPlane() const {
  return p->ui.viewPlaneType->currentText();
}

int RenderSettingsWidget::samplesPerPixel() const {
  return p->ui.samplesPerPixel->value();
}

int RenderSettingsWidget::maxRecursionDepth() const {
  return p->ui.maxRecursionDepth->value();
}

int RenderSettingsWidget::renderThreads() const {
  return p->ui.renderThreads->value();
}

int RenderSettingsWidget::queueSize() const {
  return p->ui.queueSize->value();
}

bool RenderSettingsWidget::showProgressIndicators() const {
  return p->ui.showProgressIndicators->isChecked();
}

void RenderSettingsWidget::setBusy(bool busy) {
  p->ui.resolution->setEnabled(!busy);
  p->ui.viewPlaneType->setEnabled(!busy);
  p->ui.samplerType->setEnabled(!busy);
  p->ui.samplesPerPixel->setEnabled(!busy);
  p->ui.maxRecursionDepth->setEnabled(!busy);
  p->ui.renderThreads->setEnabled(!busy);
  p->ui.queueSize->setEnabled(!busy);
  p->ui.showProgressIndicators->setEnabled(!busy);

  p->ui.renderButton->setEnabled(!busy);
  p->ui.stopButton->setEnabled(busy);
}

void RenderSettingsWidget::setElapsedTime(int milliseconds) {
  int seconds = milliseconds / 1000;
  p->ui.timeLabel->setText(
    QString("Elapsed time: %1:%2:%3")
      .arg(seconds / 3600)
      .arg((seconds % 3600) / 60, 2, 10, QLatin1Char('0'))
      .arg(seconds % 60, 2, 10, QLatin1Char('0'))
  );
}

void RenderSettingsWidget::render() {
  emit renderClicked();
}

void RenderSettingsWidget::stop() {
  emit stopClicked();
}

#include "RenderSettingsWidget.moc"
