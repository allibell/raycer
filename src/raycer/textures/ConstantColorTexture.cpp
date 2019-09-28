#include "raycer/textures/ConstantColorTexture.h"
#include "core/math/Ray.h"
#include "core/math/HitPoint.h"

using namespace raycer;

Colord ConstantColorTexture::evaluate(const Rayd&, const HitPoint&) const {
  return m_color;
}
