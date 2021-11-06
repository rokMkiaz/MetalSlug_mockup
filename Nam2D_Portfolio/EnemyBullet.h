#pragma once
#include "Bullet.h"

#include"Effect.h"

namespace Enemybullet
{
	namespace Soldier
	{

		class SoldierBullet : public Bullet
		{
		public:

			Engine::Rendering::Image::Component Hitbox;

			float FireAngle = 0.0f;
			float speed = 980.f;
			float acceleration = 1.0f;  //감속도
			float gravity = 5.0f;     //중력
			float randboost = 0.0f;



			SoldierBullet();
			virtual void Start(Vector<2> location, float angle) override;
			virtual void Update() override;
			virtual void End() override;
		};

		class SoldierEffect : public Effect
		{
		public:

			Engine::Rendering::Image::Component Hitbox;

			SoldierEffect();
			virtual void Start(Vector<2> location) override;
			virtual void Update() override;
			virtual void End() override;
		};




	}

	namespace Tank
	{
		class TankBullet : public Bullet
		{
		public:
		
			Engine::Rendering::Image::Component Hitbox;

			float FireAngle = 0.0f;
			float speed = 1200.f;
			float acceleration = 1.0f;  //감속도
			float gravity = 5.0f;     //중력
			float randboost = 0.0f;



			TankBullet();
			virtual void Start(Vector<2> location, float angle) override;
			virtual void Update() override;
			virtual void End() override;
		};

		class TankEffect : public Effect
		{
		public:

			Engine::Rendering::Image::Component Hitbox;

			TankEffect();
			virtual void Start(Vector<2> location) override;
			virtual void Update() override;
			virtual void End() override;
		};




	}

	namespace Boss
	{

		class BossMainBullet : public Bullet
		{
		public:

			Engine::Rendering::Image::Component Hitbox;

			float FireAngle = 0.0f;
			float speed = 200.f;
			float acceleration = 1.0f;  
			float gravity = 5.0f;     //중력



			BossMainBullet();
			virtual void Start(Vector<2> location, float angle) override;
			virtual void Update() override;
			virtual void End() override;
		};

		class BossMainBulletffect : public Effect
		{
		public:

			Engine::Rendering::Image::Component Hitbox;

			BossMainBulletffect();
			virtual void Start(Vector<2> location) override;
			virtual void Update() override;
			virtual void End() override;
		};
		class BossSubStart : public Bullet
		{
		public:

			Engine::Rendering::Image::Component Hitbox;

	
			float speed = 800.f;
			float Startpoint = 0.0f;
			float acceleration = 1.0f;
			float gravity = 5.0f;     //중력



			BossSubStart();
			virtual void Start(Vector<2> location, float angle) override;
			virtual void Update() override;
			virtual void End() override;
		};

		class BossSubBullet : public Bullet
		{
		public:

			Engine::Rendering::Image::Component Hitbox;

			float FireAngle = 0.0f;
			float speed = 30.f;
		
			float gravity = 5.0f;    



			BossSubBullet();
			virtual void Start(Vector<2> location, float angle) override;
			virtual void Update() override;
			virtual void End() override;
		};



	}


}




