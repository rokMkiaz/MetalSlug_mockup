#pragma once
#include "Engine\Rendering.h"
#include "Engine\Physics.h"
#include"Engine\Quadrangle.h"

#include "Stage.h"
#include"Actor.h"
#include "Cam.h"

class Stage1 :    public Stage
{
public:
	virtual   void    Start() final override;
	virtual  Stage* Update()  final override;
	virtual   void	    End() final override;


	Engine::Rendering::Animation::Component_Window MissionStart;
	Engine::Rendering::Animation::Component_Window Clear;
	Engine::Rendering::Image::Component_Window Hpbar;
	Engine::Rendering::Image::Component_Window Hp;
	Engine::Rendering::Image::Component_Window PlayerImage;
	float delay = 0.0f;


	
	float MaxHp = 0.0f;

public:
	Engine::Rendering::Image::Component Map;
	Engine::Physics::Component<Quadrangle> Ground;
	Engine::Rendering::Image::Component Groundphysics;

public:
	Stage1();
	bool Wavve1 = false;
	bool Wavve2 = false;
	bool Wavve3 = false;
	bool BossStage = false;

	bool PlayerDie = false;
	bool BossDie = false;

	float BossStageTime = 0.0f;

	unsigned int  Count = 0;

	class Actor* Player = nullptr;

	class Actor* EnemySoldier[40] = { 0 };
	class Actor* EnemyTank[10] =    { 0 };
	class Actor* Boss = nullptr;

	
	class Cam *Slugcam= nullptr;

	class StageCam :public Cam
	{
	public:
		
		virtual   void    Start() final override
		{
			cam.Location = Vector<2>(700, 250);
			cam.Sight = Vector<2>(1180, 620);
		}
		virtual   void   Update() final override
		{
			cam.Set();
		}
		virtual   void	    End() final override
		{
		}
	}stageCam1;
	class StageCam2 :public Cam
	{
	public:

		virtual   void    Start() final override
		{
			cam.Location = Vector<2>(2700, 250);
			cam.Sight = Vector<2>(1180, 620);
		}
		virtual   void   Update() final override
		{
			cam.Set();
		}
		virtual   void	    End() final override
		{
		}
	}stageCam2;




};

