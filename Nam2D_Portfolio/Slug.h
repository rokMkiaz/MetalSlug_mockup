#pragma once
#include"Engine\Rendering.h"
#include"Engine\Quadrangle.h"
#include"Engine\Physics.h"
#include"Engine\Time.h"
#include"Engine\Input.h"

#include "Actor.h"
#include "Cam.h"
#include "Bullet.h"
#include "Effect.h"
#include "SlugBullet.h"
namespace
{
	enum SlugState
	{
		Slug_Idle = 0,
		Slug_Move,
		Slug_Attack,
		Slug_Hit = 3,
		Slug_HMFire,
		Slug_Invincible,
	};
}
class Slug final:    public Actor
{
	~Slug();


public:
	
	class Slugarray
		{
		public:
			Engine::Rendering::Animation::Component Skin;
			Engine::Rendering::Animation::Component Gun;
			Engine::Physics::Component<Quadrangle> Hitbox;

			Engine::Rendering::Animation::Component Invincible;

			//Demo
			Engine::Rendering::Image::Component Hitboxprint;

			Engine::Rendering::Animation::Component Shoteffect;
			Engine::Rendering::Animation::Component HMeffect;

		public:

			bool Die = false;
			bool invincible=false;
			float InvincibleTime = 0.0f;

			Slugarray();
			void Moving(float const speed, Vector<2> vector);

			Vector<2> BombLocation() { return Shoteffect.Location; }
			Vector<2> HMGunLocation()   { return HMeffect.Location; }
		       	float HMGunAngle()      { return HMeffect.Angle; }

			void Rendering(SlugState state);


		}*Slugbody;

	class SlugCam : public Cam
	{
	public:
		
		virtual   void    Start() final override
		{
			cam.Location = Vector<2>(600, 250);
			cam.Sight    = Vector<2>(1180, 620);
		}
		virtual   void   Update() final override
		{
			cam.Set();
		}
		virtual   void	    End() final override
		{
		}

	}Slugcam;


	
public:
	//Bomb
	float delay = 0.0f;

	//HM
	int Fire = 0;
	bool HMBulletSwitch = false;


	int BulletNum = 14;
	SlugBullet::HeavyMachineGun::HMBullet hmbullet[15];
	SlugBullet::Bomb::BombBullet  BBbullet;

	bool Hitmotion=false;

	bool BossStage = false;

	
	float speed = 200.f;
	bool Attackmotion = false;

public:
	virtual void Start()  final override;
	virtual void Update() final override;
	virtual void End()    final override;

	virtual  float Location() final override;
	virtual   void SelectLocation(Vector<2> location) final override { }

	virtual   void Deathmotion(int num) final override { Hitmotion = true; Slugbody->Skin.Playback = 0.0f; }
	virtual   void  Target(Actor* target)final override {  }

};

