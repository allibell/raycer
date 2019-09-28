#include "raycer/Raycer.h"
#include "raycer/State.h"
#include "core/math/Vector.h"
#include "core/math/Ray.h"
#include "raycer/primitives/Scene.h"
#include "core/Buffer.h"
#include "core/math/HitPoint.h"
#include "core/math/HitPointInterval.h"
#include "raycer/materials/Material.h"
#include "core/math/Matrix.h"
#include "core/math/Rect.h"
#include "core/math/IntegerDecomposition.h"
#include "raycer/cameras/Camera.h"
#include "core/Exception.h"
#include "core/ScopeExit.h"

#include "raycer/cameras/PinholeCamera.h"

#include <QThreadPool>
#include <QRunnable>

#include <vector>
#include <cmath>

#include <iostream>

using namespace std;
using namespace raycer;

namespace {
  class RenderTask : public QRunnable {
  public:
    inline RenderTask(std::shared_ptr<Raycer> rt, std::shared_ptr<Camera> c, Buffer<unsigned int>& b, const Recti& r)
      : QRunnable(),
        active(false),
        raycer(rt),
        camera(c),
        buffer(b),
        rect(r)
    {
      setAutoDelete(false);
    }

    inline virtual void run() {
      try {
        active = true;
        camera->render(raycer, buffer, rect);
      } catch(Exception& e) {
        e.printBacktrace();
      }
      active = false;
    }

    bool active;
    std::shared_ptr<Raycer> raycer;
    std::shared_ptr<Camera> camera;
    Buffer<unsigned int>& buffer;
    Recti rect;
  };
}

struct Raycer::Private {
  inline Private()
    : queueSize(QThread::idealThreadCount()),
      maximumRecursionDepth(5),
      showProgressIndicators(false)
  {
    threadPool = new QThreadPool;
  }

  QThreadPool* threadPool;
  list<shared_ptr<RenderTask>> tasks;
  int queueSize;
  int maximumRecursionDepth;
  bool showProgressIndicators;
};

Raycer::Raycer(Scene* scene)
  : m_camera(std::make_shared<PinholeCamera>()),
    m_scene(scene),
    p(std::make_unique<Private>())
{
}

Raycer::Raycer(std::shared_ptr<Camera> camera, Scene* scene)
  : m_camera(camera),
    m_scene(scene),
    p(std::make_unique<Private>())
{
}

Raycer::~Raycer() {
}

void Raycer::render(Buffer<unsigned int>& buffer) {
  if (!m_scene) {
    buffer.clear();
    return;
  }

  p->tasks.clear();

  m_camera->viewPlane()->setup(m_camera->matrix(), buffer.rect());
  m_camera->setShowProgressIndicators(p->showProgressIndicators);

  IntegerDecomposition d(p->queueSize);
  for (int vert = 0; vert != d.first(); ++vert) {
    for (int horz = 0; horz != d.second(); ++horz) {
      auto task = std::make_shared<RenderTask>(shared_from_this(), m_camera, buffer, Recti(
        floor(double(buffer.width()) / d.second() * horz),
        floor(double(buffer.height()) / d.first() * vert),
        ceil(double(buffer.width()) / d.second()),
        ceil(double(buffer.height()) / d.first())
      ));

      p->tasks.push_back(task);
      p->threadPool->start(task.get());
    }
  }

  p->threadPool->waitForDone();
}

const Primitive* Raycer::primitiveForRay(const Rayd& ray) const {
  return rayState(ray).hitPoint.primitive();
}

State Raycer::rayState(const Rayd& ray) const {
  State state;
  state.startTrace();
  rayColor(ray, state);
  return state;
}

Colord Raycer::rayColor(const Rayd& ray, State& state) const {
  state.recurseIn();
  ScopeExit sx([&] { state.recurseOut(); });

  if (state.recursionDepth == p->maximumRecursionDepth) {
    state.recordEvent(nullptr, "Raycer: maximum recursion depth reached, returning black");
    return Colord::black();
  }

  HitPointInterval hitPoints;

  auto primitive = m_scene->intersect(ray, hitPoints, state);
  if (primitive) {
    auto hitPoint = hitPoints.minWithPositiveDistance();

    if (state.recursionDepth == 1) {
      state.hitPoint = hitPoint;
    }

    if (primitive->material()) {
      state.recordEvent(nullptr, "Raycer: shading material");
      return primitive->material()->shade(this, ray, hitPoint, state);
    } else {
      state.recordEvent(nullptr, "Raycer: no material found, returning black");
      return Colord::black();
    }
  } else {
    state.recordEvent(nullptr, "Raycer: Nothing hit, returning background color");
    return m_scene->background();
  }
}

void Raycer::cancel() {
  m_camera->cancel();
}

void Raycer::uncancel() {
  m_camera->uncancel();
}

std::list<Recti> Raycer::activeRects() const {
  std::list<Recti> result;
  for (const auto& task : p->tasks) {
    if (task->active) {
      result.push_back(task->rect);
    }
  }
  return result;
}

void Raycer::setMaximumRecursionDepth(int depth) {
  p->maximumRecursionDepth = depth;
}

void Raycer::setMaximumThreads(int threads) {
  p->threadPool->setMaxThreadCount(threads);
}

void Raycer::setQueueSize(int queue) {
  p->queueSize = queue;
}

void Raycer::setShowProgressIndicators(bool show) {
  p->showProgressIndicators = show;
}
