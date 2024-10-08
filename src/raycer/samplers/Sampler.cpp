#include "raycer/samplers/Sampler.h"

using namespace raycer;

void Sampler::setup(int numSamples, int numSets) {
  m_numSamples = numSamples;
  m_numSets = numSets;
  
  for (int i = 0; i != m_numSets; ++i) {
    m_sampleSets.push_back(generateSet());
  }
}
