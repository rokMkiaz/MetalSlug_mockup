#pragma once
#include"Engine\Physics.h"
#include"Engine\Quadrangle.h"

#include"Bullet.h"
#include"Effect.h"

class Actor abstract
{
public:
	virtual   void    Start() abstract;
	virtual   void   Update() abstract;
	virtual   void	    End() abstract;

	virtual   float Location() abstract;
	virtual   void SelectLocation(Vector<2> location) abstract;

	virtual   void  Deathmotion(int num) abstract;
	virtual   void  Target(Actor* target) abstract;

	Bullet*  bullet1 =  nullptr;
	Bullet * bullet2[15]; 

	int Hp = 0;

	Engine::Physics::Component<Quadrangle> Actorphysics;
};