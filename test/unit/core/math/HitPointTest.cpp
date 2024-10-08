#include "gtest.h"
#include "core/math/HitPoint.h"
#include "raycer/primitives/Box.h"

#include <cmath>

#include <sstream>

using namespace std;

namespace HitPointTest {
  static raycer::Box* box = new raycer::Box(Vector3d::null(), Vector3d::one());
  
  TEST(HitPoint, ShouldInitialize) {
    HitPoint point;
  }
  
  TEST(HitPoint, ShouldInitializeWithValues) {
    HitPoint point(box, 3, Vector3d(1, 0, 0), Vector3d(0, 1, 0));
    ASSERT_EQ(box, point.primitive());
    ASSERT_EQ(3, point.distance());
    ASSERT_EQ(Vector3d(1, 0, 0), point.point());
    ASSERT_EQ(Vector3d(0, 1, 0), point.normal());
  }
  
  TEST(HitPoint, ShouldAssign) {
    HitPoint point;
    point = HitPoint(box, 3, Vector3d(1, 0, 0), Vector3d(0, 1, 0));
    ASSERT_EQ(box, point.primitive());
    ASSERT_EQ(3, point.distance());
    ASSERT_EQ(Vector3d(1, 0, 0), point.point());
    ASSERT_EQ(Vector3d(0, 1, 0), point.normal());
  }
  
  TEST(HitPoint, ShouldSetPrimitive) {
    HitPoint point;
    point.setPrimitive(box);
    ASSERT_EQ(box, point.primitive());
  }
  
  TEST(HitPoint, ShouldSetDistance) {
    HitPoint point;
    point.setDistance(4);
    ASSERT_EQ(4, point.distance());
  }
  
  TEST(HitPoint, ShouldSetPoint) {
    HitPoint point;
    point.setPoint(Vector3d(1, 0, 0));
    ASSERT_EQ(Vector3d(1, 0, 0), point.point());
  }
  
  TEST(HitPoint, ShouldSetNormal) {
    HitPoint point;
    point.setNormal(Vector3d(0, 1, 0));
    ASSERT_EQ(Vector3d(0, 1, 0), point.normal());
  }
  
  TEST(HitPoint, ShouldCompareSameHitPointForEquality) {
    HitPoint point;
    ASSERT_TRUE(point == point);
  }
  
  TEST(HitPoint, ShouldCompareEqualHitPointsForEquality) {
    HitPoint point1(box, 3, Vector3d(1, 0, 0), Vector3d(0, 1, 0)),
             point2(box, 3, Vector3d(1, 0, 0), Vector3d(0, 1, 0));
    ASSERT_TRUE(point1 == point2);
  }
  
  TEST(HitPoint, ShouldCompareUnequalHitPointsForEquality) {
    HitPoint point1(box, 3, Vector3d(1, 0, 0), Vector3d(0, 1, 0)),
             point2(box, 4, Vector3d(0, 1, 0), Vector3d(0, 1, 0));
    ASSERT_FALSE(point1 == point2);
  }
  
  TEST(HitPoint, ShouldCompareHitPointsByDistance) {
    HitPoint point1(box, 3, Vector3d(1, 0, 0), Vector3d(0, 1, 0)),
             point2(box, 4, Vector3d(0, 1, 0), Vector3d(0, 1, 0));
    ASSERT_TRUE(point1 < point2);
    ASSERT_FALSE(point2 < point1);
  }
  
  TEST(HitPoint, ShouldProvideUndefinedHitPoint) {
    HitPoint point = HitPoint::undefined();
    ASSERT_EQ(nullptr, point.primitive());
    ASSERT_TRUE(isnan(point.distance()));
    ASSERT_TRUE(point.point().isUndefined());
    ASSERT_TRUE(point.normal().isUndefined());
  }
  
  TEST(HitPoint, ShouldReturnTrueIfHitPointIsUndefined) {
    HitPoint point = HitPoint::undefined();
    ASSERT_TRUE(point.isUndefined());
  }
  
  TEST(HitPoint, ShouldReturnFalseIfHitPointIsNotUndefined) {
    HitPoint point;
    ASSERT_FALSE(point.isUndefined());
  }
  
  TEST(HitPoint, ShouldReturnHitPointWithSwappedNormal) {
    HitPoint point(box, 3, Vector3d(1, 0, 0), Vector3d(0, 1, 0)),
             expected(box, 3, Vector3d(1, 0, 0), Vector3d(0, -1, 0));
    ASSERT_TRUE(expected == point.swappedNormal());
  }
  
  TEST(HitPoint, ShouldTransformHitpointWithPointMatrix) {
    Vector4d point(1, 0, 0);
    Vector3d normal(0, 1, 0);
    HitPoint hp(box, 3, point, normal);
    Matrix4d pointMatrix = Matrix3d::rotateX(1_radians);
    Vector3d expectedPoint = pointMatrix * point;
    HitPoint transformed = hp.transform(pointMatrix, Matrix3d());
    ASSERT_EQ(expectedPoint, transformed.point());
  }

  TEST(HitPoint, ShouldTransformHitpointWithPointAndNormalMatrixes) {
    Vector3d point(1, 0, 0), normal(0, 1, 0);
    HitPoint hp(box, 3, point, normal);
    Matrix3d normalMatrix = Matrix3d::rotateZ(1_radians);
    Vector3d expectedNormal = normalMatrix * normal;
    HitPoint transformed = hp.transform(Matrix3d(), normalMatrix);
    ASSERT_EQ(expectedNormal, transformed.normal());
  }

  TEST(HitPoint, ShouldNotAlterDistanceWhenTransforming) {
    Vector3d point(1, 0, 0), normal(0, 1, 0);
    HitPoint hp(box, 3, point, normal);
    Matrix4d pointMatrix = Matrix3d::rotateX(1_radians);
    HitPoint transformed = hp.transform(pointMatrix, Matrix3d());
    ASSERT_EQ(hp.distance(), transformed.distance());
  }
  
  TEST(HitPoint, ShouldStreamHitPointToString) {
    Vector3d point(1, 0, 0), normal(0, 1, 0);
    HitPoint hp(box, 3, point, normal);
    
    ostringstream str;
    str << hp;
    
    ASSERT_EQ("((1, 0, 0, 1) (0, 1, 0), 3)", str.str());
  }
}
