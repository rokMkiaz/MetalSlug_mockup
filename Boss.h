#pragma once
#include "Actor.h"
#include"EnemyBullet.h"



enum BossState
{
	Boss_Idle1 = 0,
	Boss_Idle2 = 1,
	Boss_Move,
	Boss_Attack_Main,
	Boss_Attack_Sub,
	Boss_Death,
	Boss_Intro

};
namespace Enemy
{
	class Boss : public Actor
	{
	public:
		class Bossarray
		{
		public:

			Engine::Rendering::Animation::Component MainGun;
			Engine::Rendering::Animation::Component SubGun;
			Engine::Rendering::Animation::Component Body[3];

			Engine::Physics::Component<Quadrangle> Hitbox[2];
			Engine::Physics::Component<Quadrangle> Search;

			Engine::Rendering::Animation::Component MainEffect;
			Engine::Rendering::Animation::Component SubEffect;
			Engine::Rendering::Animation::Component Cap[3];

			//Demo
			Engine::Rendering::Image::Component Hitboxprint;

			Engine::Rendering::Animation::Component Bomb;


		public:
			bool Left = false;
			bool Motion = false;
			bool SubAttack = false;
			float IntroTime = 0.0f;

			Bossarray();

			void Moving(float const speed, Vector<2> vector);

			void Rendering(BossState state);


		}*Bossbody;

		Enemybullet::Boss::BossMainBullet  Bomb;
		Enemybullet::Boss::BossSubStart Startshot[9];
		Enemybullet::Boss::BossSubBullet SubBomb[9];

		float MainGunCooldown = 0.0f;
		int SubCount = 0;
		float SubTime = 0.0f;

		bool Intro = false;
		bool Battle = false;
	

		float MainGunFire = 0.0f;
		float SubGunFire = 0.0f;



		Actor* PlayerTarget = nullptr;

		virtual void Start()final override;
		virtual void Update()final override;
		virtual void End()final override;
		virtual float Location() override;
		virtual void SelectLocation(Vector<2> location)final override;
		virtual void Deathmotion(int num)final override {};
		virtual void Target(Actor* target)final override { PlayerTarget = target; };
	};

}