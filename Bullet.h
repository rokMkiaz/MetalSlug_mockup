#pragma once
#include"Engine\Rendering.h"
#include"Engine\Quadrangle.h"
#include"Engine\Physics.h"

#include"Effect.h"


class Bullet
{
public:

	virtual   void    Start(Vector<2> location,float angle) abstract;
	virtual   void   Update() abstract;
	virtual   void	    End() abstract;

	bool Fly=false;
	unsigned int Damage = 0;

	class Effect*effect=nullptr;

	Engine::Rendering::Animation::Component Bolt;
	Engine::Physics::Component<Quadrangle> Hit;
    Vector<2> VulletLocation() { return Bolt.Location; }


};

