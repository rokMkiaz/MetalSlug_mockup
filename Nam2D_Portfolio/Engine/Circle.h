#pragma once
#include"Point.h"

class Circle
{
public:
	Circle();
	Circle(float const & radius, Point const & center);
public:
	float Radius = float(0);
	Point Center = Point(0,0);

};

