#pragma once

#include "world/objects/Element.h"

namespace raycer {
  class Material;
}

/**
  * Abstract base class for materials.
  */
class Material : public Element {
  Q_OBJECT

public:
  /**
    * Returns the default material, which is a black matte material.
    */
  static Material* defaultMaterial();

  /**
    * Default constructor.
    */
  explicit Material(Element* parent = nullptr);

  /**
    * Converts this material to the corresponding class in the raycer
    * namespace.
    */
  virtual std::shared_ptr<raycer::Material> toRaycerMaterial() const = 0;
};
