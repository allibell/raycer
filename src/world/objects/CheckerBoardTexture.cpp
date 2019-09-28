#include "world/objects/ElementFactory.h"
#include "world/objects/CheckerBoardTexture.h"
#include "raycer/textures/CheckerBoardTexture.h"
#include "raycer/textures/mappings/PlanarMapping2D.h"

CheckerBoardTexture::CheckerBoardTexture(Element* parent)
  : Texture(parent),
    m_brightTexture(nullptr),
    m_darkTexture(nullptr)
{
}

std::shared_ptr<raycer::Texturec> CheckerBoardTexture::toRaycerTexture() const {
  return make_named<raycer::CheckerBoardTexture>(
    new raycer::PlanarMapping2D,
    textureOrDefault(brightTexture())->toRaycerTexture(),
    textureOrDefault(darkTexture())->toRaycerTexture()
  );
}

static bool dummy = ElementFactory::self().registerClass<CheckerBoardTexture>("CheckerBoardTexture");

#include "CheckerBoardTexture.moc"
