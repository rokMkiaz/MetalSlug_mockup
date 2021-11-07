#include<cmath>

#include"Circle.h"
#include"Quadrangle.h"
#include"Point.h"

#include "Physics.h"


namespace Engine::Physics
{
	template<typename Shape>
	Component<Shape>::Component()
	{

	}
	template<typename Shape>
	Component<Shape>::Component(Shape const& shape) : Shape(shape)
	{

	}

	template Component<Point>::Component(); 
	template Component<Point>::Component(Point const &);

	template<>
	template<>
	bool Component<Point>::Collide(Component<Circle>const& component) const
	{
	
		return sqrtf(powf(component.Center.x - x, 2) + powf(component.Center.y - y, 2)) <= component.Radius;
	}

	template<>
	template<>
	bool Component<Point>::Collide(Component<Quadrangle> const& component) const
	{
		Point const min = Point(component.Center.x - component.Length.x / 2, component.Center.y - component.Length.y / 2);
		Point const max = Point(component.Center.x + component.Length.x / 2, component.Center.y + component.Length.y / 2);

		return (min.x <= x and x <= max.x) and (min.y <= y and y <= max.y);
	}



	template Component<Circle>::Component(); 
	template Component<Circle>::Component(Circle const&);

	template<>
	template<>
	bool Component<Circle>::Collide(Component<Point>const& component) const
	{

		return component.Collide(*this);
	}
	template<>
	template<>
	bool Component<Circle>::Collide(Component<Circle>const& component) const
	{
		return sqrtf(powf(component.Center.x-this->Center.x,2)+powf(component.Center.y-this->Center.y,2))<=component.Radius+this->Radius;
	}
	template<>
	template<>
	bool Component<Circle>::Collide(Component<Quadrangle>const& component) const
	{
		Point min = Point(component.Center.x - component.Length.x / 2, component.Center.y - component.Length.y / 2);
		Point max = Point(component.Center.x + component.Length.x / 2, component.Center.y + component.Length.y / 2);

		if ((min.x <= Center.x and Center.x <= max.x) or (min.y <= Center.y and Center.y <= max.y))
		{

			return (min.x - this->Radius <= Center.x and Center.x <= max.x + this->Radius) and (min.y - this->Radius <= Center.y and Center.y <= max.y + this->Radius);
		}
		else
		{
			return Component<Point>(Point(min.x, min.y)).Collide(*this) or
				   Component<Point>(Point(max.x, min.y)).Collide(*this) or
			       Component<Point>(Point(min.x, max.y)).Collide(*this) or
			       Component<Point>(Point(max.x, max.y)).Collide(*this);
		}
	}


	template Component<Quadrangle>::Component(); 
	template Component<Quadrangle>::Component(Quadrangle const&);

	template<>
	template<>
	bool Component<Quadrangle>::Collide(Component<Point>const& component) const
	{
		return component.Collide(*this);
	}
	template<>
	template<>
	bool Component<Quadrangle>::Collide(Component<Circle>const& component) const
	{
		return component.Collide(*this);
	}
	template<>
	template<>
	bool Component<Quadrangle>::Collide(Component<Quadrangle>const& component) const
	{
		Point const min[2]
		{
			Point(Center.x - Length.x / 2                    ,                     Center.y - Length.y / 2),
			Point(component.Center.x - component.Length.x / 2, component.Center.y - component.Length.y / 2)
		};

		Point const max[2]
		{
			Point(Center.x + Length.x / 2                    ,                     Center.y + Length.y / 2),
			Point(component.Center.x + component.Length.x / 2, component.Center.y + component.Length.y / 2)
		};

		return min[0].x <= max[1].x and min[1].x <= max[0].x and min[0].y <= max[1].y and min[1].y <= max[0].y;


	}
	
}


