#ifndef _RECT_H_
#define _RECT_H_

#include <iostream>
#include "Vec2.hpp"

class Rect
{
public:
  float x, y, w, h;

  Rect();

  Rect(float x, float y, float w, float h);

  float distance(float x, float y);

  double inclination();

  double inclination_two_points(Rect box);

  Rect rotate(double angle);

  void sum_vec(Vec2 vector);

  std::pair<float, float> get_center();

  std::pair<float, float> distance_between_centers(Rect box);

  bool is_point_in(float x, float y);

};

#endif
