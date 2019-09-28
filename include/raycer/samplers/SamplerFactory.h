#pragma once

#include "core/Factory.h"
#include "core/Singleton.h"
#include "raycer/samplers/Sampler.h"

namespace raycer {
  typedef Singleton<Factory<Sampler>> SamplerFactory;
}
