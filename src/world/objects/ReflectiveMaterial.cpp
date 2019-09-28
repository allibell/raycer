#include "world/objects/ElementFactory.h"
#include "world/objects/ReflectiveMaterial.h"
#include "world/objects/Texture.h"

#include "raycer/materials/ReflectiveMaterial.h"

ReflectiveMaterial::ReflectiveMaterial(Element* parent)
  : PhongMaterial(parent),
    m_reflectionColor(Colord::white()),
    m_reflectionCoefficient(0.5)
{
}

std::shared_ptr<raycer::Material> ReflectiveMaterial::toRaycerMaterial() const {
  auto material = make_named<raycer::ReflectiveMaterial>(
    textureOrDefault(diffuseTexture())->toRaycerTexture(), specularColor()
  );
  material->setAmbientCoefficient(ambientCoefficient());
  material->setDiffuseCoefficient(diffuseCoefficient());
  material->setExponent(exponent());
  material->setSpecularCoefficient(specularCoefficient());
  material->setReflectionColor(reflectionColor());
  material->setReflectionCoefficient(reflectionCoefficient());

  return material;
}

static bool dummy = ElementFactory::self().registerClass<ReflectiveMaterial>("ReflectiveMaterial");

#include "ReflectiveMaterial.moc"
