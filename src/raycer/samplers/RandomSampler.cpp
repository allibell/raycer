#include "raycer/samplers/RandomSampler.h"
#include "raycer/samplers/SamplerFactory.h"

#include "core/math/Range.h"

using namespace raycer;
using namespace std;

std::vector<Vector2d> RandomSampler::generateSet() {
  vector<Vector2d> result;
  
  Ranged range(0, 1);
  
  for (int i = 0; i != numSamples(); ++i) {
    Vector2d sample(range.random(), range.random());
    result.push_back(sample);
  }
  
  return result;
}

static bool dummy = SamplerFactory::self().registerClass<RandomSampler>("RandomSampler");
