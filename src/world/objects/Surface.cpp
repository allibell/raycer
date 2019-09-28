#include "world/objects/Surface.h"
#include "world/objects/Material.h"
#include "world/objects/Light.h"
#include "raycer/primitives/Instance.h"
#include "raycer/primitives/Composite.h"
#include "raycer/primitives/Scene.h"
#include "raycer/primitives/Grid.h"

Surface::Surface(Element* parent)
  : Transformable(parent),
    m_material(nullptr),
    m_visible(true)
{
}

std::shared_ptr<raycer::Primitive> Surface::applyTransform(std::shared_ptr<raycer::Primitive> primitive) const {
  auto result = std::make_shared<raycer::Instance>(primitive);
  result->setMatrix(localTransform());
  return result;
}

std::shared_ptr<raycer::Primitive> Surface::toRaycer(raycer::Scene* scene) const {
  auto primitive = toRaycerPrimitive();
  if (!primitive) {
    return primitive;
  }
  
  if (material()) {
    primitive->setMaterial(material()->toRaycerMaterial());
  }
  
  if (childElements().size() > 0) {
    auto composite = std::dynamic_pointer_cast<raycer::Composite>(primitive);
    if (!composite) {
      composite = std::make_shared<raycer::Composite>();
      composite->add(primitive);
    }
    
    for (const auto& child : childElements()) {
      if (Surface* surface = qobject_cast<Surface*>(child)) {
        if (surface->visible())
          composite->add(surface->toRaycer(scene));
      } else if (Light* light = qobject_cast<Light*>(child)) {
        if (light->visible())
          scene->addLight(light->toRaycer());
      }
    }
    
    if (auto grid = std::dynamic_pointer_cast<raycer::Grid>(composite)) {
      grid->setup();
    }

    return applyTransform(composite);
  } else {
    return applyTransform(primitive);
  }
}

bool Surface::canHaveChild(Element* child) const {
  return dynamic_cast<Surface*>(child) != nullptr ||
         dynamic_cast<Light*>(child) != nullptr;
}

#include "Surface.moc"
