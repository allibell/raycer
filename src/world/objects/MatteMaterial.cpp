#include "world/objects/ElementFactory.h"
#include "world/objects/MatteMaterial.h"
#include "world/objects/Texture.h"

#include "raycer/materials/MatteMaterial.h"

MatteMaterial::MatteMaterial(Element* parent)
  : Material(parent),
    m_diffuseTexture(nullptr),
    m_ambientCoefficient(1),
    m_diffuseCoefficient(1)
{
}

std::shared_ptr<raycer::Material> MatteMaterial::toRaycerMaterial() const {
  auto material = make_named<raycer::MatteMaterial>(
    textureOrDefault(diffuseTexture())->toRaycerTexture()
  );
  material->setAmbientCoefficient(ambientCoefficient());
  material->setDiffuseCoefficient(diffuseCoefficient());

  return material;
}

static bool dummy = ElementFactory::self().registerClass<MatteMaterial>("MatteMaterial");

#include "MatteMaterial.moc"
