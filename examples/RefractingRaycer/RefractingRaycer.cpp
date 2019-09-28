#include "raycer/Raycer.h"
#include "raycer/primitives/Scene.h"
#include "raycer/primitives/Sphere.h"
#include "raycer/primitives/Plane.h"
#include "raycer/lights/PointLight.h"
#include "raycer/materials/Material.h"
#include "raycer/materials/PhongMaterial.h"
#include "raycer/materials/ReflectiveMaterial.h"
#include "raycer/materials/TransparentMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"
#include "widgets/QtDisplay.h"

#include <QApplication>

using namespace raycer;

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  auto scene = new Scene(Colord(0.4, 0.4, 0.4));

  auto sphere = std::make_shared<Sphere>(Vector3d(0, 1, 0), 1);
  auto glass = std::make_shared<TransparentMaterial>();
  glass->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0.1, 0.1, 0.1)));
  glass->setRefractionIndex(1.52);
  sphere->setMaterial(glass);

  auto sphere2 = std::make_shared<Sphere>(Vector3d(-2.5, 1, 0), 1);
  auto green = std::make_shared<ReflectiveMaterial>();
  green->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0, 1, 0)));
  green->setSpecularColor(Colord(0.2, 0.2, 0.2));
  sphere2->setMaterial(green);

  auto sphere3 = std::make_shared<Sphere>(Vector3d(2.5, 1, 0), 1);
  auto red = std::make_shared<ReflectiveMaterial>();
  red->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(1, 0, 0)));
  red->setSpecularColor(Colord(0.2, 0.2, 0.2));
  sphere3->setMaterial(red);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 2);
  auto blue = std::make_shared<PhongMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));
  plane->setMaterial(blue);

  scene->add(sphere);
  scene->add(sphere2);
  scene->add(sphere3);
  scene->add(plane);

  auto light1 = std::make_shared<PointLight>(Vector3d(-3, -3, -1), Colord(0.4, 0.4, 0.4));
  scene->addLight(light1);

  auto raycer = std::make_shared<Raycer>(scene);
  auto display = new QtDisplay(0, raycer);

  display->show();

  return app.exec();
}
