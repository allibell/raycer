#include "SceneFactory.h"

#include "raycer/primitives/Triangle.h"
#include "raycer/primitives/Disk.h"
#include "raycer/primitives/Rectangle.h"
#include "raycer/primitives/Plane.h"
#include "raycer/lights/PointLight.h"
#include "raycer/materials/Material.h"
#include "raycer/materials/MatteMaterial.h"
#include "raycer/textures/ConstantColorTexture.h"

using namespace raycer;

class FlatScene : public Scene {
public:
  FlatScene();

private:
  std::shared_ptr<MatteMaterial> m_red, m_green, m_blue;
};

FlatScene::FlatScene()
  : Scene()
{
  m_red = std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(1, 0, 0)));
  m_green = std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 1, 0)));
  m_blue = std::make_shared<MatteMaterial>(std::make_shared<ConstantColorTexture>(Colord(0, 0, 1)));

  setAmbient(Colord(0.4, 0.4, 0.4));

  auto triangle = std::make_shared<Triangle>(Vector3d(0, 2, 0), Vector3d(2, 2, 0), Vector3d(0, 0, 0));
  triangle->setMaterial(m_red);
  add(triangle);

  auto disk = std::make_shared<Disk>(Vector3d(3, 1, 0), Vector3d(0, 0, -1), 1);
  disk->setMaterial(m_green);
  add(disk);

  auto rectangle = std::make_shared<Rectangle>(Vector3d(-3, 2, 0), Vector3d(2, 0, 0), Vector3d(0, -2, 0));
  rectangle->setMaterial(m_blue);
  add(rectangle);

  auto plane = std::make_shared<Plane>(Vector3d(0, -1, 0), 2);
  plane->setMaterial(m_blue);

  add(plane);

  auto light1 = std::make_shared<PointLight>(Vector3d(-3, -3, -1), Colord(0.4, 0.4, 0.4));
  addLight(light1);
}

static bool dummy = SceneFactory::self().registerClass<FlatScene>("Flat");
