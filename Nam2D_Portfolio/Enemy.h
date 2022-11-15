#pragma once
#include "Actor.h"
#include"Slug.h"
#include"EnemyBullet.h"
namespace
{
	enum EnemyState
	{
		Enemy_Idle = 0,
		Enemy_Move,
		Enemy_Attack,
		Enemy_BombHit,
		Enemy_Hit1 = 4,
		Enemy_Hit2 = 5,
		Enemy_Hit3 = 6
	};
}
namespace Enemy
{
	namespace Soldier
	{
		class Soldier : public Actor
		{
		public:
			~Soldier();

			class Soldierarray
			{
			public:

				Engine::Rendering::Animation::Component Skin;
				Engine::Physics::Component<Quadrangle> Hitbox;
				Engine::Physics::Component<Quadrangle> Search;

			

				//Demo
				Engine::Rendering::Image::Component Hitboxprint;

				Engine::Rendering::Animation::Component Bomb;
	

			public:
				Soldierarray();
			
				void Moving(float const speed, Vector<2> vector);

				Vector<2> BombLocation() { return Bomb.Location; }

				void Rendering(EnemyState state);


			}*Soldierbody;


			float speed = 180.0f;
			bool Motion = false;
			bool AttackMotion = false;
			float  RandFire = 2.0f; //사거리,사격각도


			int DieMotion = 0;
			

			
			Actor *  PlayerTarget =nullptr ;
			

		public:
			Enemybullet::Soldier::SoldierBullet Bomb;
			

		public:
			virtual void Start()     final override;
			virtual void Update()    final override;
			virtual void End()       final override;

			virtual void Deathmotion(int num) final override { DieMotion = num; }

			virtual float Location() final override  {return 0.0f; }
			virtual   void SelectLocation(Vector<2> location) final override;
			virtual   void  Target(Actor* target)final override { PlayerTarget = target; }

		};

	}



	namespace Tank
	{
		class Tank : public Actor
		{
		public:
			~Tank();

			class Tankarray
			{
			public:

				Engine::Rendering::Animation::Component Skin;
				Engine::Physics::Component<Quadrangle> Hitbox;
				Engine::Physics::Component<Quadrangle> Search;

				Engine::Rendering::Animation::Component FireEffect;
		
				//Demo
				Engine::Rendering::Image::Component Hitboxprint;

			


			public:
				Tankarray();

				void Moving(float const speed, Vector<2> vector);

				

				void Rendering(EnemyState state);


			}*Tankbody;


			float speed = 200.0f;
			bool Motion = false;
			bool AttackMotion = false;
			float       RandFire = 2.0f;


			int DieMotion = 3;



			Actor* PlayerTarget = nullptr;
		

		public:
			Enemybullet::Tank::TankBullet Bomb;
			
			//Enemybullet::Soldier::SoldierBullet Bomb;


		public:
			virtual void Start()     final override;
			virtual void Update()    final override;
			virtual void End()       final override;

			virtual void Deathmotion(int num) final override { }

			virtual float Location() final override { return 0.0f; }
			virtual   void SelectLocation(Vector<2> location) final override;
			virtual   void  Target(Actor* target)final override { PlayerTarget = target; }

		};
	}
}

