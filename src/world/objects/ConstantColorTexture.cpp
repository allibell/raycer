#include "world/objects/ElementFactory.h"
#include "world/objects/ConstantColorTexture.h"
#include "raycer/textures/ConstantColorTexture.h"

ConstantColorTexture::ConstantColorTexture(Element* parent)
  : Texture(parent),
    m_color(Colord::black())
{
}

std::shared_ptr<raycer::Texturec> ConstantColorTexture::toRaycerTexture() const {
  return make_named<raycer::ConstantColorTexture>(m_color);
}

static bool dummy = ElementFactory::self().registerClass<ConstantColorTexture>("ConstantColorTexture");

#include "ConstantColorTexture.moc"
