#include "widgets/world/RenderWindow.h"
#include "widgets/world/RenderSettingsWidget.h"

#include "widgets/RenderWidget.h"

#include "raycer/Raycer.h"
#include "raycer/lights/PointLight.h"
#include "raycer/primitives/Scene.h"
#include "raycer/cameras/Camera.h"

#include "raycer/samplers/SamplerFactory.h"
#include "raycer/viewplanes/ViewPlaneFactory.h"

#include "world/objects/Scene.h"
#include "world/objects/Camera.h"

#include <QGridLayout>
#include <QScrollArea>
#include <QTime>

using namespace raycer;

struct RenderWindow::Private {
  inline Private()
    : renderWidget(nullptr),
      settingsWidget(nullptr),
      busy(false),
      timer(0)
  {
  }

  RenderWidget* renderWidget;
  RenderSettingsWidget* settingsWidget;

  std::shared_ptr<raycer::Raycer> raycer;

  bool busy;
  int timer;
  QTime time;
};

RenderWindow::RenderWindow(QWidget* parent)
  : QWidget(parent),
    p(std::make_unique<Private>())
{
  p->raycer = std::make_shared<Raycer>(nullptr);

  auto grid = new QGridLayout(this);
  p->settingsWidget = new RenderSettingsWidget(this);
  auto scrollArea = new QScrollArea(this);
  p->renderWidget = new RenderWidget(scrollArea, p->raycer);
  scrollArea->setWidget(p->renderWidget);

  grid->addWidget(p->settingsWidget, 0, 0);
  grid->addWidget(scrollArea, 0, 1);

  setLayout(grid);

  connect(p->settingsWidget, SIGNAL(renderClicked()), this, SLOT(render()));
  connect(p->settingsWidget, SIGNAL(stopClicked()), this, SLOT(stop()));

  connect(p->renderWidget, SIGNAL(finished()), this, SLOT(finished()));
}

QSize RenderWindow::sizeHint() const {
  return QSize(1024, 768);
}

void RenderWindow::timerEvent(QTimerEvent*) {
  if (isBusy()) {
    p->settingsWidget->setElapsedTime(p->time.elapsed());
  }
}

bool RenderWindow::isBusy() const {
  return p->busy;
}

void RenderWindow::render() {
  p->busy = true;
  p->time.restart();

  p->settingsWidget->setBusy(true);

  p->renderWidget->resize(p->settingsWidget->resolution());
  p->renderWidget->setBufferSize(p->settingsWidget->resolution());

  auto samplerClass = p->settingsWidget->sampler().toStdString() + "Sampler";
  auto sampler = SamplerFactory::self().createShared(samplerClass);
  // 83 is an arbitrary number, but it's a relatively large prime number, so
  // it's unlikely to introduce aliasing patterns
  sampler->setup(p->settingsWidget->samplesPerPixel(), 83);

  auto viewPlaneClass = p->settingsWidget->viewPlane().toStdString();
  auto viewPlane = ViewPlaneFactory::self().createShared(viewPlaneClass);
  viewPlane->setSampler(sampler);

  p->raycer->camera()->setViewPlane(viewPlane);
  p->raycer->setMaximumRecursionDepth(p->settingsWidget->maxRecursionDepth());
  p->raycer->setMaximumThreads(p->settingsWidget->renderThreads());
  p->raycer->setQueueSize(p->settingsWidget->queueSize());

  p->raycer->setShowProgressIndicators(p->settingsWidget->showProgressIndicators());
  p->renderWidget->setShowProgressIndicators(p->settingsWidget->showProgressIndicators());

  p->renderWidget->render();

  p->timer = startTimer(1000);
}

void RenderWindow::stop() {
  p->renderWidget->stop();
  finished();
}

void RenderWindow::finished() {
  p->settingsWidget->setBusy(false);
  p->busy = false;
}

void RenderWindow::setScene(::Scene* scene) {
  auto raycerScene = scene->toRaycerScene();

  p->raycer->setScene(raycerScene);

  auto camera = scene->activeCamera();
  if (camera) {
    p->raycer->setCamera(camera->toRaycer());
  } else {
    p->raycer->camera()->setPosition(
      Matrix3d::rotateY(-25_degrees) *
      Matrix3d::rotateX(-25_degrees) *
      Vector3d(0, 0, -5)
    );
  }
}

#include "RenderWindow.moc"
