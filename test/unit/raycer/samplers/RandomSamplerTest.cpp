#include "gtest.h"
#include "raycer/samplers/RandomSampler.h"

namespace RandomSamplerTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(RandomSampler, ShouldConstructWithParameters) {
    RandomSampler sampler;
    sampler.setup(4, 1);
    ASSERT_EQ(4, sampler.numSamples());
  }
}
