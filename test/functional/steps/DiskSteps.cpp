#include "test/functional/support/RaycerFeatureTest.h"
#include "test/functional/support/GivenWhenThen.h"
#include "test/helpers/ShapeRecognition.h"

#include "raycer/primitives/Disk.h"

using namespace testing;
using namespace raycer;

GIVEN(RaycerFeatureTest, "a centered disk") {
  auto disk = std::make_shared<Disk>(Vector3d::null(), Vector3d(0, 0, -1), 1);
  disk->setMaterial(test->redDiffuse());
  test->add(disk);
}

GIVEN(RaycerFeatureTest, "a displaced disk") {
  auto disk = std::make_shared<Disk>(Vector3d(0, 20, 0), Vector3d(0, 0, -1), 1);
  disk->setMaterial(test->redDiffuse());
  test->add(disk);
}

THEN(RaycerFeatureTest, "i should see the disk") {
  ShapeRecognition rec;
  ASSERT_TRUE(rec.recognizeCircle(test->buffer()));
}

THEN(RaycerFeatureTest, "i should not see the disk") {
  ShapeRecognition rec;
  ASSERT_FALSE(rec.recognizeCircle(test->buffer()));
}
