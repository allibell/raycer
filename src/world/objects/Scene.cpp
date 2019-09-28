#include "world/objects/Scene.h"
#include "world/objects/Surface.h"
#include "world/objects/Camera.h"
#include "world/objects/Light.h"
#include "raycer/primitives/Scene.h"
#include "raycer/primitives/Grid.h"

#include <QMap>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

Scene::Scene(Element* parent)
  : Element(parent),
    m_changed(false),
    m_ambient(Colord(0.4, 0.4, 0.4)),
    m_background(Colord(0.4, 0.8, 1))
{
  setName("New Scene");
}

raycer::Scene* Scene::toRaycerScene() const {
  raycer::Scene* result = new raycer::Scene();

  auto grid = make_named<raycer::Grid>();
  for (const auto& child : childElements()) {
    if (auto surface = dynamic_cast<Surface*>(child)) {
      if (surface->visible()) {
        auto primitive = surface->toRaycer(result);
        if (primitive && !primitive->boundingBox().isInfinite()) {
          grid->add(primitive);
        }
      }
    } else if (auto light = dynamic_cast<Light*>(child)) {
      if (light->visible()) {
        result->addLight(light->toRaycer());
      }
    }
  }

  if (grid->primitives().size() > 0) {
    grid->setup();
    result->add(grid);
  }

  result->setAmbient(ambient());
  result->setBackground(background());

  return result;
}

bool Scene::save(const QString& filename) {
  QFile file(filename);

  if (!file.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't write file.");
    return false;
  }

  QJsonObject object;
  write(object);

  QJsonDocument saveDoc(object);
  file.write(saveDoc.toJson());

  m_changed = false;

  return true;
}

bool Scene::load(const QString& filename) {
  QFile file(filename);

  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't read file.");
    return false;
  }

  QByteArray data = file.readAll();

  QJsonDocument loadDoc(QJsonDocument::fromJson(data));

  read(loadDoc.object());

  QMap<QString, Element*> references;
  findReferences(this, references);
  resolveReferences(references);

  return true;
}

Camera* Scene::activeCamera() const {
  Camera* camera = nullptr;
  for (const auto& child : childElements()) {
    if (qobject_cast<Camera*>(child)) {
      camera = static_cast<Camera*>(child);
    }
  }
  return camera;
}

void Scene::findReferences(Element* root, QMap<QString, Element*>& references) {
  references[root->id()] = root;

  for (const auto& child : root->childElements()) {
    findReferences(child, references);
  }
}

bool Scene::canHaveChild(Element*) const {
  return true;
}

#include "Scene.moc"
