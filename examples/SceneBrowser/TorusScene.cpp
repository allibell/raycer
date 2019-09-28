#include "SceneFactory.h"

#include "raycer/primitives/Plane.h"
#include "raycer/primitives/Torus.h"
#include "raycer/primitives/Instance.h"
#include "raycer/lights/PointLight.h"
#include "raycer/materials/Material.h"
#include "raycer/materials/MatteMaterial.h"
#include "raycer/materials/TransparentMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

using namespace raycer;

class TorusScene : public Scene {
public:
  TorusScene();

private:
  std::shared_ptr<TransparentMaterial> m_glass;
  std::shared_ptr<MatteMaterial> m_blue;
};

TorusScene::TorusScene()
  : Scene()
{
  m_glass = std::make_shared<TransparentMaterial>();
  m_blue = std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));

  setAmbient(Colord(0.4, 0.4, 0.4));

  m_glass->setSpecularColor(Colord(0.5, 0.5, 0.5));
  m_glass->setDiffuseTexture(std::make_shared<ConstantColorTexture>(Colord(0.0, 0.1, 0.1)));
  m_glass->setAmbientCoefficient(0.2);
  m_glass->setDiffuseCoefficient(0);
  m_glass->setRefractionIndex(1.52);

  auto torus = std::make_shared<Torus>(2, 1);
  auto instance = std::make_shared<Instance>(torus);
  instance->setMatrix(Matrix3d::rotateX(90_degrees));
  instance->setMaterial(m_glass);
  add(instance);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 4);
  plane->setMaterial(m_blue);

  add(plane);

  auto light1 = std::make_shared<PointLight>(Vector3d(-18, -18, -6), Colord(0.4, 0.4, 0.4));
  addLight(light1);
}

static bool dummy = SceneFactory::self().registerClass<TorusScene>("Torus");
