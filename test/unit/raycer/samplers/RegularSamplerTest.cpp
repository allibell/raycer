#include "gtest.h"
#include "raycer/samplers/RegularSampler.h"

namespace RegularSamplerTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(RegularSampler, ShouldConstructWithParameters) {
    RegularSampler sampler;
    sampler.setup(4, 1);
    ASSERT_EQ(4, sampler.numSamples());
  }
  
  TEST(RegularSampler, ShouldBeEquallySpacedHorizontally) {
    RegularSampler sampler;
    sampler.setup(4, 1);
    auto set = sampler.sampleSet();
    ASSERT_EQ(set[1] - set[0], set[3] - set[2]);
  }
  
  TEST(RegularSampler, ShouldBeEquallySpacedVertically) {
    RegularSampler sampler;
    sampler.setup(4, 1);
    auto set = sampler.sampleSet();
    ASSERT_EQ(set[2] - set[0], set[3] - set[1]);
  }
}
