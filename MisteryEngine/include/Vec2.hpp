#ifndef _VEC_H_
#define _VEC_H_

#include <iostream>
class Vec2
{
public:
  float x, y;

  Vec2();

  Vec2(float x, float y);

  Vec2 operator + (const Vec2 &vector);

  Vec2 operator - (const Vec2 &vector);

  Vec2 operator * (const int &scalar);

  float magnitude(Vec2 vector);

  Vec2 normalise();

  float distance(float x, float y);

  double inclination();

  double inclination_two_points(Vec2 vector);

  Vec2 rotate(double angle);

  double radians_to_degrees(float angle_in_radians);

};

#endif