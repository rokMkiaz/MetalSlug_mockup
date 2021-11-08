#pragma once

#include"Engine\Time.h"


#include"Bullet.h"
#include"Effect.h"

namespace SlugBullet
{
	namespace HeavyMachineGun
	{
		class HMBullet : public Bullet
		{
		public:




			//Demo
			Engine::Rendering::Image::Component Hitbox;


			float speed = 1000.f;

			HMBullet();

			virtual void Start(Vector<2> location, float angle) override;
			virtual void Update() override;
			virtual void End()    override;


		};

	}

	namespace Bomb
	{
		class BombBullet : public Bullet
		{
		public:


			//Demo
			Engine::Rendering::Image::Component Hitbox;


			BombBullet();

			Vector<2> StartLocation = Vector<2>(0, 0); 

			float speed = 800.f;
			float acceleration = 1.0f;  
			float gravity = 10.0f;     



			virtual void Start(Vector<2> location, float angle) override;
			virtual void Update() override;
			virtual void End()    override;
		};

		class Bombeffect : public Effect
		{
		public:

			Engine::Rendering::Image::Component Hitbox;


			Bombeffect();

			virtual void Start(Vector<2> location)  final override;
			virtual void Update()		         final override;
			virtual void End()			 final override;
		};

	}
}
