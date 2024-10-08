#include "SceneFactory.h"

#include "raycer/primitives/Sphere.h"
#include "raycer/primitives/Box.h"
#include "raycer/primitives/Plane.h"
#include "raycer/lights/PointLight.h"
#include "raycer/primitives/Difference.h"
#include "raycer/primitives/Intersection.h"
#include "raycer/primitives/Union.h"
#include "raycer/primitives/Instance.h"
#include "raycer/materials/Material.h"
#include "raycer/materials/PhongMaterial.h"
#include "raycer/materials/TransparentMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

using namespace raycer;

class WineglassScene : public Scene {
public:
  WineglassScene();

private:
  std::shared_ptr<TransparentMaterial> m_glass;
  std::shared_ptr<PhongMaterial> m_blue;
};

WineglassScene::WineglassScene()
  : Scene()
{
  m_glass = std::make_shared<TransparentMaterial>();
  m_blue = std::make_shared<PhongMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));

  setAmbient(Colord(0.4, 0.4, 0.4));

  auto sphere = std::make_shared<Sphere>(Vector3d(0, -1, 0), 1);
  auto sphere2 = std::make_shared<Sphere>(Vector3d(0, -1, 0), 0.95);
  auto box = std::make_shared<Box>(Vector3d(0, -2, 0), Vector3d(1, 0.5, 1));
  auto d = std::make_shared<Difference>();
  d->add(sphere);
  d->add(sphere2);
  d->add(box);

  m_glass->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0.1, 0.1, 0.1)));
  m_glass->setRefractionIndex(1.52);

  auto instance = std::make_shared<Instance>(d);
  instance->setMatrix(Matrix4d::translate(Vector3d(1.5, 0, 0)));
  instance->setMaterial(m_glass);

  add(instance);

  instance = std::make_shared<Instance>(d);
  instance->setMatrix(Matrix4d::translate(Vector3d(-1.5, 0, 0)));
  instance->setMaterial(m_glass);
  add(instance);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 2);
  plane->setMaterial(m_blue);
  add(plane);

  auto light1 = std::make_shared<PointLight>(Vector3d(-3, -3, -1), Colord(0.4, 0.4, 0.4));
  addLight(light1);
}

static bool dummy = SceneFactory::self().registerClass<WineglassScene>("Wine glasses");
