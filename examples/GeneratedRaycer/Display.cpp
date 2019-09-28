#include <QVBoxLayout>
#include <QSpacerItem>

#include <QMouseEvent>

#include "Display.h"
#include "raycer/Raycer.h"
#include "raycer/State.h"
#include "raycer/primitives/Primitive.h"
#include "raycer/primitives/Scene.h"
#include "raycer/lights/PointLight.h"
#include "raycer/cameras/PinholeCamera.h"
#include "core/math/HitPointInterval.h"

#include "widgets/world/PropertyEditorWidget.h"

#include "world/objects/Scene.h"
#include "world/objects/Sphere.h"

using namespace std;

Display::Display(QWidget* parent)
  : QtDisplay(parent, std::make_shared<raycer::Raycer>(nullptr))
{
}

Display::~Display() {
}

void Display::setScene(Scene* scene) {
  if (m_raycer->scene()) {
    stop();
    delete m_raycer->scene();
  }

  auto raycerScene = scene->toRaycerScene();

  m_raycer->setScene(raycerScene);
  render();
}

void Display::mousePressEvent(QMouseEvent* event) {
  QtDisplay::mousePressEvent(event);

  if (event->modifiers() & Qt::ControlModifier) {
    Rayd ray = m_raycer->camera()->rayForPixel(event->pos().x(), event->pos().y());
    if (ray.direction().isDefined()) {
      auto state = m_raycer->rayState(ray);

      cout << state.hitPoint.primitive() << " - " << state.hitPoint << endl;
      cout << "numRays: " << state.numRays << endl;
      cout << "maxRecursionDepth: " << state.maxRecursionDepth << endl;
      cout << "intersectionHits: " << state.intersectionHits << endl;
      cout << "intersectionMisses: " << state.intersectionMisses << endl;
      cout << "shadowIntersectionHits: " << state.shadowIntersectionHits << endl;
      cout << "shadowIntersectionMisses: " << state.shadowIntersectionMisses << endl;

      for (const auto& event : *state.events) {
        cout << event << endl;
      }
    }
  }
}

#include "Display.moc"
