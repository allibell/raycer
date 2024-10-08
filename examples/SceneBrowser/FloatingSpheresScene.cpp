#include "SceneFactory.h"

#include "raycer/primitives/Sphere.h"
#include "raycer/primitives/Plane.h"
#include "raycer/lights/PointLight.h"
#include "raycer/materials/Material.h"
#include "raycer/materials/MatteMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

using namespace raycer;

class FloatingSpheresScene : public Scene {
public:
  FloatingSpheresScene();

private:
  std::shared_ptr<MatteMaterial> m_red, m_green, m_blue;
};

FloatingSpheresScene::FloatingSpheresScene()
  : Scene()
{
  m_red = std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(1, 0, 0)));
  m_green = std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 1, 0)));
  m_blue = std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));

  setAmbient(Colord(0.1, 0.1, 0.1));

  auto sphere = std::make_shared<Sphere>(Vector3d(0, 0, 0), 1);
  sphere->setMaterial(m_red);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 1);
  plane->setMaterial(m_blue);

  auto sphere2 = std::make_shared<Sphere>(Vector3d(-2, -2, 2), 1);
  sphere2->setMaterial(m_green);

  auto sphere3 = std::make_shared<Sphere>(Vector3d(2, -2, 2), 1);
  sphere3->setMaterial(m_blue);

  add(sphere);
  add(sphere2);
  add(sphere3);
  add(plane);

  auto light1 = std::make_shared<PointLight>(Vector3d(-3, -3, -1), Colord(0.4, 0.4, 0.4));
  auto light2 = std::make_shared<PointLight>(Vector3d( 3, -3, -1), Colord(0.4, 0.4, 0.4));
  auto light3 = std::make_shared<PointLight>(Vector3d(-3, -3,  1), Colord(0.4, 0.4, 0.4));
  auto light4 = std::make_shared<PointLight>(Vector3d( 3, -3,  1), Colord(0.4, 0.4, 0.4));
  addLight(light1);
  addLight(light2);
  addLight(light3);
  addLight(light4);
}

static bool dummy = SceneFactory::self().registerClass<FloatingSpheresScene>("Floating Spheres");
