#include "SceneFactory.h"

#include "raycer/primitives/Scene.h"
#include "raycer/primitives/Grid.h"
#include "raycer/primitives/Sphere.h"
#include "raycer/primitives/Box.h"
#include "raycer/primitives/Plane.h"
#include "raycer/lights/PointLight.h"
#include "raycer/primitives/Difference.h"
#include "raycer/materials/Material.h"
#include "raycer/materials/PhongMaterial.h"
#include "raycer/materials/ReflectiveMaterial.h"
#include "raycer/materials/TransparentMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

using namespace raycer;

class DiceScene : public Scene {
public:
  DiceScene();

private:
  std::shared_ptr<ReflectiveMaterial> m_red;
  std::shared_ptr<TransparentMaterial> m_glass;
  std::shared_ptr<PhongMaterial> m_blue;
};

DiceScene::DiceScene()
  : Scene()
{
  m_red = std::make_shared<ReflectiveMaterial>();
  m_glass = std::make_shared<TransparentMaterial>();
  m_blue = std::make_shared<PhongMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));

  setAmbient(Colord(0.4, 0.4, 0.4));

  auto grid = std::make_shared<Grid>();

  auto box = std::make_shared<Box>(Vector3d(0, 1, 0), Vector3d(1, 1, 1));
  auto sphere2 = std::make_shared<Sphere>(Vector3d(1.8, 1, 0), 1);
  auto sphere3 = std::make_shared<Sphere>(Vector3d(-1.8, 1, 0), 1);
  auto sphere4 = std::make_shared<Sphere>(Vector3d(0, 1, 1.8), 1);
  auto sphere5 = std::make_shared<Sphere>(Vector3d(0, 1, -1.8), 1);
  auto d = std::make_shared<Difference>();
  d->add(box);
  d->add(sphere2);
  d->add(sphere3);
  d->add(sphere4);
  d->add(sphere5);

  m_glass->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0.1, 0.1, 0.1)));
  m_glass->setRefractionIndex(1.52);

  d->setMaterial(m_glass);

  grid->add(d);

  auto sphere6 = std::make_shared<Sphere>(Vector3d(2.5, 1, 0), 1);
  m_red->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(1, 0, 0)));
  m_red->setSpecularColor(Colord(0.2, 0.2, 0.2));
  sphere6->setMaterial(m_red);
  grid->add(sphere6);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 2);
  plane->setMaterial(m_blue);
  add(plane);
  grid->setup();
  add(grid);

  auto light1 = std::make_shared<PointLight>(Vector3d(-3, -3, -1), Colord(0.4, 0.4, 0.4));
  addLight(light1);
}

static bool dummy = SceneFactory::self().registerClass<DiceScene>("Dice");
