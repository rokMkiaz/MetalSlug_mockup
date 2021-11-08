#pragma once
#include"Engine\Rendering.h"
#include"Engine\Quadrangle.h"
#include"Engine\Physics.h"




class Effect
{
public:
	virtual   void    Start(Vector<2> location) abstract;
	virtual   void   Update() abstract;
	virtual   void	    End() abstract;

	unsigned int Damage = 0;
	bool Check = false;
	Engine::Physics::Component<Quadrangle> Hit;
	Engine::Rendering::Animation::Component effect;

};

