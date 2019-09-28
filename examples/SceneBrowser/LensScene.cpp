#include "SceneFactory.h"

#include "raycer/primitives/Sphere.h"
#include "raycer/primitives/Plane.h"
#include "raycer/lights/PointLight.h"
#include "raycer/primitives/Intersection.h"
#include "raycer/primitives/Union.h"
#include "raycer/materials/Material.h"
#include "raycer/materials/PhongMaterial.h"
#include "raycer/materials/ReflectiveMaterial.h"
#include "raycer/materials/TransparentMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

using namespace raycer;

class LensScene : public Scene {
public:
  LensScene();

private:
  std::shared_ptr<ReflectiveMaterial> m_red;
  std::shared_ptr<TransparentMaterial> m_glass;
  std::shared_ptr<PhongMaterial> m_blue;
};

LensScene::LensScene()
  : Scene()
{
  m_red = std::make_shared<ReflectiveMaterial>();
  m_glass = std::make_shared<TransparentMaterial>();
  m_blue = std::make_shared<PhongMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));

  setAmbient(Colord(0.4, 0.4, 0.4));

  auto sphere1 = std::make_shared<Sphere>(Vector3d(0, 1, 0), 1);
  auto sphere2 = std::make_shared<Sphere>(Vector3d(1, 1, 0), 1);
  auto i = std::make_shared<Intersection>();
  i->add(sphere1);
  i->add(sphere2);

  m_glass->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0.1, 0.1, 0.1)));
  m_glass->setRefractionIndex(1.52);

  i->setMaterial(m_glass);

  auto sphere3 = std::make_shared<Sphere>(Vector3d(3, 1, 0), 1);
  m_red->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(1, 0, 0)));
  m_red->setSpecularColor(Colord(0.2, 0.2, 0.2));
  sphere3->setMaterial(m_red);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 2);
  plane->setMaterial(m_blue);

  add(i);
  add(sphere3);
  add(plane);

  auto light1 = std::make_shared<PointLight>(Vector3d(-3, -3, -1), Colord(0.4, 0.4, 0.4));
  addLight(light1);
}

static bool dummy = SceneFactory::self().registerClass<LensScene>("Lens");
