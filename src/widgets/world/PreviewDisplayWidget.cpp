#include "widgets/world/PreviewDisplayWidget.h"
#include "world/objects/Material.h"
#include "world/objects/Camera.h"
#include "world/objects/Scene.h"
#include "raycer/primitives/Scene.h"
#include "raycer/primitives/Sphere.h"
#include "raycer/primitives/Plane.h"
#include "raycer/materials/MatteMaterial.h"
#include "raycer/Raycer.h"
#include "raycer/lights/DirectionalLight.h"
#include "raycer/textures/CheckerBoardTexture.h"
#include "raycer/textures/ConstantColorTexture.h"
#include "raycer/textures/mappings/PlanarMapping2D.h"
#include "raycer/cameras/PinholeCamera.h"

PreviewDisplayWidget::PreviewDisplayWidget(QWidget* parent)
  : QtDisplay(parent, std::make_shared<raycer::Raycer>(nullptr))
{
}

PreviewDisplayWidget::~PreviewDisplayWidget() {
}

QSize PreviewDisplayWidget::sizeHint() const {
  return QSize(256, 25);
}

void PreviewDisplayWidget::clear() {
  updateScene([&]() {
    m_raycer->setScene(nullptr);
  });
}

void PreviewDisplayWidget::setMaterial(Material* material, Scene* s) {
  setInteractive(true);
  updateScene([&]() {
    m_raycer->setScene(sphereOnPlane(material, s));
    m_raycer->setCamera(std::make_shared<raycer::PinholeCamera>());
  });
}

void PreviewDisplayWidget::setCamera(Camera* camera, Scene* scene) {
  setInteractive(false);
  updateScene([&]() {
    m_raycer->setScene(scene->toRaycerScene());
    m_raycer->setCamera(camera->toRaycer());
  });
}

void PreviewDisplayWidget::updateScene(const std::function<void()>& setup) {
  if (m_raycer->scene()) {
    stop();
    delete m_raycer->scene();
  }

  setup();

  render();
}

raycer::Scene* PreviewDisplayWidget::sphereOnPlane(Material* material, Scene* s) const {
  auto mat = material->toRaycerMaterial();
  auto scene = new raycer::Scene;

  scene->setAmbient(s->ambient());
  scene->setBackground(s->background());

  auto sphere = std::make_shared<raycer::Sphere>(Vector3d(0, 0, 0), 2);
  sphere->setMaterial(mat);

  auto planeMaterial = std::make_shared<raycer::MatteMaterial>(
    std::make_shared<raycer::CheckerBoardTexture>(
      new raycer::PlanarMapping2D,
      std::make_shared<raycer::ConstantColorTexture>(Colord::black()),
      std::make_shared<raycer::ConstantColorTexture>(Colord::white())
    )
  );

  auto plane = std::make_shared<raycer::Plane>(Vector3d(0, -1, 0), 2);
  plane->setMaterial(planeMaterial);

  scene->add(sphere);
  scene->add(plane);

  auto light = std::make_shared<raycer::DirectionalLight>(Vector3d(-0.5, -1, -0.5), Colord(1, 1, 1));
  scene->addLight(light);

  return scene;
}

#include "PreviewDisplayWidget.moc"
