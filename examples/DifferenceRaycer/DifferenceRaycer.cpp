#include "raycer/Raycer.h"
#include "raycer/primitives/Scene.h"
#include "raycer/primitives/Sphere.h"
#include "raycer/primitives/Plane.h"
#include "raycer/lights/PointLight.h"
#include "raycer/primitives/Difference.h"
#include "raycer/primitives/Intersection.h"
#include "raycer/primitives/Union.h"
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

  auto sphere1 = std::make_shared<Sphere>(Vector3d(0, 1, 0), 1);
  auto sphere2 = std::make_shared<Sphere>(Vector3d(1.8, 1, 0), 1);
  auto sphere3 = std::make_shared<Sphere>(Vector3d(-1.8, 1, 0), 1);
  auto sphere4 = std::make_shared<Sphere>(Vector3d(0, 1, 1.8), 1);
  auto sphere5 = std::make_shared<Sphere>(Vector3d(0, 1, -1.8), 1);
  auto d = std::make_shared<Difference>();
  d->add(sphere1);
  d->add(sphere2);
  d->add(sphere3);
  d->add(sphere4);
  d->add(sphere5);

  auto glass = std::make_shared<TransparentMaterial>();
  glass->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0.1, 0.1, 0.1)));
  glass->setRefractionIndex(1.52);

  d->setMaterial(glass);

  auto sphere6 = std::make_shared<Sphere>(Vector3d(2.5, 1, 0), 1);

  auto red = std::make_shared<ReflectiveMaterial>();
  red->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(1, 0, 0)));
  red->setSpecularColor(Colord(0.2, 0.2, 0.2));
  sphere6->setMaterial(red);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 2);

  auto blue = std::make_shared<PhongMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));
  plane->setMaterial(blue);

  scene->add(d);
  scene->add(sphere6);
  scene->add(plane);

  auto light1 = std::make_shared<PointLight>(Vector3d(-3, -3, -1), Colord(0.4, 0.4, 0.4));
  scene->addLight(light1);

  auto raycer = std::make_shared<Raycer>(scene);
  auto display = new QtDisplay(0, raycer);

  display->show();

  return app.exec();
}
