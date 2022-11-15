#include<cmath>

#include "EnemyBullet.h"
#include"Engine\Time.h"
#include"SlugBullet.h"



namespace Enemybullet
{
	namespace Soldier
	{
		SoldierBullet::SoldierBullet()
		{
			Bolt.Name = "Animation/Enemy/Soldier/Bomb";
			Bolt.Duration = 4.0f;
			Bolt.Length = Vector<2>(35, 35);
			Bolt.Repeatable = true;
			Bolt.Flipped = true;

			effect = new SoldierEffect;

			Hitbox.Name = "Image/GBB";
		}
		SoldierBullet::~SoldierBullet()
		{
			delete effect;
			effect = NULL;
		}
		void SoldierBullet::Start(Vector<2> location, float angle)
		{
			Damage = 1;
			Bolt.Location = location + Vector<2>(0, 50);
			FireAngle = angle;

			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };
			Hit.Length = { Bolt.Length[0],Bolt.Length[1] };
			//Demo
			Hitbox.Length = Bolt.Length;
			Hitbox.Location = Bolt.Location;

		}
		void SoldierBullet::Update()
		{
			randboost += Engine::Time::Get::Delta();

			if (Fly == true)
			{

				Bolt.Render();
				//Demo
				Hitbox.Render();


				float const radian = FireAngle * (3.14159265f / 180.0f);
				float x = cos(radian) * (speed  / acceleration);
				float y = sin(radian) * (abs(speed ) / acceleration);
				Bolt.Render();

				//Demo
				Hitbox.Render();

				Bolt.Location += (Vector<2>(-x, y - gravity) * Engine::Time::Get::Delta());
				if (Bolt.Playback >= 0.2f) acceleration += 4 * Engine::Time::Get::Delta(), gravity += 300 * Engine::Time::Get::Delta();
				Bolt.Angle += 360.0f * Engine::Time::Get::Delta();



				Hit.Center = { Bolt.Location[0],Bolt.Location[1] };
				//Demo
				Hitbox.Location = { Bolt.Location[0],Bolt.Location[1] };
				Hitbox.Angle = Bolt.Angle;
			}
			if (randboost > 5.0f)randboost = 0.0f;

		}
		void SoldierBullet::End()
		{
			
			effect->Start(Bolt.Location);

			Bolt.Location = Vector<2>(0, 0);
			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };




			Bolt.Angle = 0.0f;
			Bolt.Playback = 0.0f;
			acceleration = 1.0f;
			gravity = 10.0f;
			Fly = false;
		}

		SoldierEffect::SoldierEffect()
		{
			effect.Name = "Animation/Enemy/Soldier/Bombeffect";
			effect.Duration = 0.5f;
			effect.Length = Vector<2>(50, 50);



			effect.Repeatable = false;

		}
		void SoldierEffect::Start(Vector<2> location)
		{

			Damage = 1;
			effect.Location = { location[0],location[1] + (effect.Length[1] / 2) - 20.0f };


			Hit.Center = { effect.Location[0],effect.Location[1] };
			Hit.Length = { effect.Length[0] , effect.Length[1] };

			Hitbox.Name = "Image/GBB";
			Hitbox.Location = effect.Location;
			Hitbox.Length = effect.Length;

			Check = true;
		}
		void SoldierEffect::Update()
		{
			if (Check == true) effect.Render(), Hitbox.Render();
		}
		void SoldierEffect::End()
		{
			if (effect.Playback >= effect.Duration)
			{
				Check = false;
				Hit.Center = { 0.0f,0.0f };
				effect.Playback = 0.0f;
			}


		}
	}


	namespace Tank
	{
		TankBullet::TankBullet()
		{
			Bolt.Name = "Animation/Enemy/Tank/Bullet";
			Bolt.Duration = 4.0f;
			Bolt.Length = Vector<2>(25, 25);
			Bolt.Repeatable = true;
			Bolt.Flipped = true;

			effect = new TankEffect;

			Hitbox.Name = "Image/GBB";

		}
		TankBullet::~TankBullet()
		{
			delete effect;
			effect = NULL;
		}
		void TankBullet::Start(Vector<2> location, float angle)
		{
			Damage = 1;
			Bolt.Location = location;
			FireAngle = angle;

			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };
			Hit.Length = { Bolt.Length[0],Bolt.Length[1] };
			//Demo
			Hitbox.Length = Bolt.Length;
			Hitbox.Location = Bolt.Location;
		}
		void TankBullet::Update()
		{
			randboost += Engine::Time::Get::Delta();
			if (Fly == true)
			{

				Bolt.Render();
				//Demo
				Hitbox.Render();


				float const radian = FireAngle * (3.14159265f / 180.0f);
				float x = cos(radian) * ((speed    - (randboost*30)) / acceleration);
				float y = sin(radian) * (abs(speed + (randboost * 30)) / (acceleration * 2));
				Bolt.Render();

				//Demo
				Hitbox.Render();
				if (Bolt.Playback < 0.5f)Bolt.Name = "Animation/Enemy/Tank/Bullet";
				else Bolt.Name = "Animation/Enemy/Tank/IceBullet";

				Bolt.Location += (Vector<2>(-x, y - gravity) * Engine::Time::Get::Delta());
				if (Bolt.Playback >= 0.2f) acceleration += 4 * Engine::Time::Get::Delta(), gravity += 300 * Engine::Time::Get::Delta();
				Bolt.Angle += 360.0f * Engine::Time::Get::Delta();



				Hit.Center = { Bolt.Location[0],Bolt.Location[1] };
				//Demo
				Hitbox.Location = { Bolt.Location[0],Bolt.Location[1] };
				Hitbox.Angle = Bolt.Angle;
			}
			if (randboost > 5.0f)randboost = 0.0f;
		}
		void TankBullet::End()
		{
			effect->Start(Bolt.Location);

			Bolt.Location = Vector<2>(0, 0);


			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };


			Bolt.Angle = 0.0f;
			Bolt.Playback = 0.0f;
			acceleration = 1.0f;
			gravity = 10.0f;
			Fly = false;
		}

		TankEffect::TankEffect()
		{
			effect.Name = "Animation/Enemy/Tank/Bombeffect";
			effect.Duration = 0.5f;
			effect.Length = Vector<2>(75, 75);



			effect.Repeatable = false;
		}
		void TankEffect::Start(Vector<2> location)
		{
			Damage = 1;
			effect.Location = { location[0],location[1] + (effect.Length[1] / 2) - 15.0f };


			Hit.Center = { effect.Location[0],effect.Location[1] };
			Hit.Length = { effect.Length[0] , effect.Length[1] };

			Hitbox.Name = "Image/GBB";
			Hitbox.Location = effect.Location;
			Hitbox.Length = effect.Length;

			Check = true;
		}
		void TankEffect::Update()
		{
			if (Check == true)
			{

				effect.Render();
				Hitbox.Render();
			}

		}
		void TankEffect::End()
		{
			if (effect.Playback >= effect.Duration)
			{
				Check = false;
				Hit.Center = { 0.0f,0.0f };
				effect.Playback = 0.0f;
			}
		}
	}


	namespace Boss
	{
		//Main weapon
		BossMainBullet::BossMainBullet()
		{
			Bolt.Name = "Animation/Enemy/Boss/Mainweapon/Bullet";
			Bolt.Duration = 3.0f;
			Bolt.Length = Vector<2>(40, 50);
			Bolt.Repeatable = true;

			
			effect = new BossMainBulletffect;
			

			Hitbox.Name = "Image/GBB";
		}
		void BossMainBullet::Start(Vector<2> location, float angle)
		{
			Damage = 2;
			Bolt.Location = location;
			Bolt.Angle = angle;

			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };
			Hit.Length = { Bolt.Length[0] - 20.f,Bolt.Length[1] - 20.f };
			//Demo
			Hitbox.Length = Bolt.Length;
			Hitbox.Location = Bolt.Location;
		}
		void BossMainBullet::Update()
		{
			if (Fly == true)
			{

				Bolt.Render();
				//Demo
				Hitbox.Render();

				float const radian = abs(Bolt.Angle) * (3.14159265f / 180.0f);
				float x = sin(radian) * speed * acceleration;
				float y = cos(radian) * speed * acceleration;


				Bolt.Location -= (Vector<2>(x, y) * Engine::Time::Get::Delta());
				if (Bolt.Playback >= 0.2f) acceleration += 4 * Engine::Time::Get::Delta();



				Hit.Center = { Bolt.Location[0],Bolt.Location[1] };
				//Demo
				Hitbox.Location = { Bolt.Location[0],Bolt.Location[1] };
				Hitbox.Angle = Bolt.Angle;
			}

		}
		void BossMainBullet::End()
		{
			effect->Start(Bolt.Location);

			Bolt.Location = Vector<2>(0, 0);


			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };


			Bolt.Angle = 0.0f;
			Bolt.Playback = 0.0f;
			acceleration = 1.0f;
			gravity = 10.0f;
			Fly = false;
		}

		BossMainBulletffect::BossMainBulletffect()
		{
			effect.Name = "Animation/Enemy/Boss/Mainweapon/Bulleteffect";
			effect.Duration = 1.5f;
			effect.Length = Vector<2>(200, 200);



			effect.Repeatable = false;
		}
		void BossMainBulletffect::Start(Vector<2> location)
		{
			Damage = 2;
			effect.Location = { location[0],location[1] + (effect.Length[1] / 2) - 15.0f };


			Hit.Center = { effect.Location[0],effect.Location[1] };
			Hit.Length = { effect.Length[0] , effect.Length[1] };

			Hitbox.Name = "Image/GBB";
			Hitbox.Location = effect.Location;
			Hitbox.Length = effect.Length;

			Check = true;
		}
		void BossMainBulletffect::Update()
		{
			if (Check == true)
			{

				effect.Render();
				Hitbox.Render();
			}
		}
		void BossMainBulletffect::End()
		{
			if (effect.Playback >= effect.Duration)
			{
				Check = false;
				Hit.Center = { 0.0f,0.0f };
				effect.Playback = 0.0f;
			}
		}


		//Sub weapon
		BossSubStart::BossSubStart()
		{
			Bolt.Name = "Animation/Enemy/Boss/Subweapon/SubFire";
			Bolt.Duration = 0.4f;
			Bolt.Length = Vector<2>(25, 30);
			Bolt.Repeatable = true;
		}
		void BossSubStart::Start(Vector<2> location, float angle)
		{
			Startpoint = location[1];
			Bolt.Location = location;
			Bolt.Angle = angle;
		}
		void BossSubStart::Update()
		{
			if (Fly == true)
			{

				Bolt.Render();
				Bolt.Location[1] += speed * acceleration * Engine::Time::Get::Delta();

				acceleration += Engine::Time::Get::Delta();
				if (Bolt.Location[1] > Startpoint + 500)End();
			}
		}
		void BossSubStart::End()
		{
			Bolt.Location = Vector<2>(0, 0);
			acceleration = 1.0f;


			Bolt.Angle = 0.0f;
			Bolt.Playback = 0.0f;

			Fly = false;

		}

		BossSubBullet::BossSubBullet()
		{
			Bolt.Name = "Animation/Enemy/Boss/Subweapon/Subbullet";
			Bolt.Duration = 1.0f;
			Bolt.Length = Vector<2>(75, 75);
			Bolt.Repeatable = true;

			effect = new SlugBullet::Bomb::Bombeffect;
			

		

			Hitbox.Name = "Image/GBB";



		}
		void BossSubBullet::Start(Vector<2> location, float angle)
		{
			Damage = 1;

			Bolt.Location = location;
			Bolt.Angle = angle;


			Hit.Center = { Bolt.Location[0],Bolt.Location[1] - 50 };
			Hit.Length = { Bolt.Length[0] - 50,Bolt.Length[1] - 50 };
			//Demo
			Hitbox.Length = { Hit.Length.x, Hit.Length.y };
			Hitbox.Location ={ Hit.Center.x, Hit.Center.y};
		}
		void BossSubBullet::Update()
		{
			if (Fly == true)
			{
				Bolt.Render();
				//Demo
				Hitbox.Render();

		
				Bolt.Location[1] -= speed * gravity * Engine::Time::Get::Delta();

			

				Hit.Center = { Bolt.Location[0],Bolt.Location[1] - 20 };
				//Demo
				Hitbox.Location = { Hit.Center.x, Hit.Center.y };
			
			}

		}
		void BossSubBullet::End()
		{
			effect->Start(Bolt.Location-Vector<2>(0,30));
		

			Bolt.Location = Vector<2>(0, 0);


			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };


			Bolt.Angle = 0.0f;
			Bolt.Playback = 0.0f;
		
			gravity = 5.0f;
			Fly = false;
		}

	}
}


