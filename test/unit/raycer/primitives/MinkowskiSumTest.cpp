#include "gtest.h"
#include "raycer/State.h"
#include "raycer/primitives/MinkowskiSum.h"
#include "test/mocks/raycer/MockPrimitive.h"

namespace MinkowskiSumTest {
  using namespace ::testing;
  using namespace raycer;
  
  TEST(MinkowskiSum, ShouldReturnFarthestPoint) {
    auto hull = std::make_shared<MinkowskiSum>();

    auto mock1 = std::make_shared<NiceMock<MockPrimitive>>();
    EXPECT_CALL(*mock1, farthestPoint(_)).WillOnce(Return(Vector3d(1, 0, 0)));
    hull->add(mock1);

    auto mock2 = std::make_shared<NiceMock<MockPrimitive>>();
    EXPECT_CALL(*mock2, farthestPoint(_)).WillOnce(Return(Vector3d(2, 0, 0)));
    hull->add(mock2);
    
    ASSERT_EQ(Vector3d(3, 0, 0), hull->farthestPoint(Vector3d::right()));
  }
}
