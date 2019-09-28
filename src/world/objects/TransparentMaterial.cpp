#include "world/objects/ElementFactory.h"
#include "world/objects/TransparentMaterial.h"
#include "world/objects/Texture.h"

#include "raycer/materials/TransparentMaterial.h"

TransparentMaterial::TransparentMaterial(Element* parent)
  : PhongMaterial(parent),
    m_refractionIndex(1),
    m_transmissionCoefficient(1)
{
}

std::shared_ptr<raycer::Material> TransparentMaterial::toRaycerMaterial() const {
  auto material = make_named<raycer::TransparentMaterial>();
  material->setAmbientCoefficient(ambientCoefficient());
  material->setDiffuseCoefficient(diffuseCoefficient());
  material->setSpecularCoefficient(specularCoefficient());
  material->setDiffuseTexture(textureOrDefault(diffuseTexture())->toRaycerTexture());
  material->setSpecularColor(specularColor());
  material->setExponent(exponent());
  material->setTransmissionCoefficient(transmissionCoefficient());
  material->setRefractionIndex(refractionIndex());
  material->setReflectionColor(reflectionColor());
  material->setReflectionCoefficient(reflectionCoefficient());

  return material;
}

static bool dummy = ElementFactory::self().registerClass<TransparentMaterial>("TransparentMaterial");

#include "TransparentMaterial.moc"
