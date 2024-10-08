#include "widgets/CameraParameterWidgetFactory.h"
#include "widgets/SphericalCameraParameterWidget.h"
#include "SphericalCameraParameterWidget.uic"
#include "raycer/cameras/SphericalCamera.h"

using namespace raycer;

struct SphericalCameraParameterWidget::Private {
  Ui::SphericalCameraParameterWidget ui;
};

SphericalCameraParameterWidget::SphericalCameraParameterWidget(QWidget* parent)
  : CameraParameterWidget(parent),
    p(std::make_unique<Private>())
{
  p->ui.setupUi(this);
  connect(p->ui.horizontalFieldOfViewSlider, SIGNAL(valueChanged(int)), this, SLOT(parameterChanged()));
  connect(p->ui.verticalFieldOfViewSlider, SIGNAL(valueChanged(int)), this, SLOT(parameterChanged()));
}

SphericalCameraParameterWidget::~SphericalCameraParameterWidget() {
}

void SphericalCameraParameterWidget::parameterChanged() {
  emit changed();
}

int SphericalCameraParameterWidget::horizontalFieldOfView() const {
  return p->ui.horizontalFieldOfViewSlider->value();
}

int SphericalCameraParameterWidget::verticalFieldOfView() const {
  return p->ui.verticalFieldOfViewSlider->value();
}

void SphericalCameraParameterWidget::applyTo(std::shared_ptr<Camera> camera) {
  auto sphericalCamera = dynamic_cast<SphericalCamera*>(camera.get());
  if (sphericalCamera) {
    sphericalCamera->setHorizontalFieldOfView(Angled::fromDegrees(horizontalFieldOfView()));
    sphericalCamera->setVerticalFieldOfView(Angled::fromDegrees(verticalFieldOfView()));
  }
}

static bool dummy = CameraParameterWidgetFactory::self().registerClass<SphericalCameraParameterWidget>("SphericalCamera");

#include "SphericalCameraParameterWidget.moc"
