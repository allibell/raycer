#include "SceneFactory.h"

#include "raycer/primitives/Sphere.h"
#include "raycer/primitives/Plane.h"
#include "raycer/lights/PointLight.h"
#include "raycer/materials/Material.h"
#include "raycer/materials/MatteMaterial.h"
#include "raycer/materials/ReflectiveMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

using namespace raycer;

class MetalSpheresScene : public Scene {
public:
  MetalSpheresScene();

private:
  std::shared_ptr<ReflectiveMaterial> m_red, m_green, m_blue;
  std::shared_ptr<MatteMaterial> m_background;
};

MetalSpheresScene::MetalSpheresScene()
  : Scene()
{
  m_background = std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));
  m_red = std::make_shared<ReflectiveMaterial>();
  m_green = std::make_shared<ReflectiveMaterial>();
  m_blue = std::make_shared<ReflectiveMaterial>();

  setAmbient(Colord(0.4, 0.4, 0.4));

  auto sphere = std::make_shared<Sphere>(Vector3d(0, 1, 0), 1);
  m_red->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(1, 0, 0)));
  m_red->setSpecularColor(Colord(0.2, 0.2, 0.2));
  m_red->setSpecularColor(Colord(0.2, 0.2, 0.2));
  sphere->setMaterial(m_red);

  auto sphere2 = std::make_shared<Sphere>(Vector3d(-2.5, 1, 0), 1);
  m_green->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0, 1, 0)));
  m_green->setSpecularColor(Colord(0.2, 0.2, 0.2));
  sphere2->setMaterial(m_green);

  auto sphere3 = std::make_shared<Sphere>(Vector3d(2.5, 1, 0), 1);
  m_blue->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));
  m_blue->setSpecularColor(Colord(0.2, 0.2, 0.2));
  sphere3->setMaterial(m_blue);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 2);
  plane->setMaterial(m_background);

  add(sphere);
  add(sphere2);
  add(sphere3);
  add(plane);

  auto light1 = std::make_shared<PointLight>(Vector3d(-3, -3, -1), Colord(0.4, 0.4, 0.4));
  addLight(light1);
}

static bool dummy = SceneFactory::self().registerClass<MetalSpheresScene>("Metal Spheres");
