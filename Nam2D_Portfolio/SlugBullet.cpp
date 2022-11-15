#include<cmath>
#include "SlugBullet.h"

namespace SlugBullet
{
	namespace HeavyMachineGun
	{
		HMBullet::HMBullet()
		{
			Bolt.Name = "Animation/SlugFile/Gun/HMBullet";
			Bolt.Duration = 0.5f;
			Bolt.Repeatable = true;
			Bolt.Length = Vector<2>(50, 10);
			//
			Hitbox.Name = "Image/GBB";


			
		}

		void HMBullet::Start(Vector<2> location, float angle)
		{
			Damage = 1;
		
			Bolt.Location = location;
			Bolt.Angle = angle;

			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };
			Hit.Length = { Bolt.Length[0],Bolt.Length[1] };
			//Demo
			Hitbox.Length = Bolt.Length;
			Hitbox.Location = Bolt.Location;

			Fly = true;

		}

		void HMBullet::Update()
		{
			if (Fly == true)
			{
				float const radian = Bolt.Angle * (3.14159265f / 180.0f);
				float x = cos(radian) * speed;
				float y = sin(radian) * speed;
				Bolt.Render();
				//Demo
				Hitbox.Render();

				Bolt.Location += (Vector<2>(x, y) * Engine::Time::Get::Delta());
				Hit.Center = { Bolt.Location[0],Bolt.Location[1] };

				//Demo
				Hitbox.Location = { Bolt.Location[0],Bolt.Location[1] };
				Hitbox.Angle = Bolt.Angle;
			}

		}

		void HMBullet::End()
		{
		

			Fly = false;
			Bolt.Location = Vector<2>(0, 0);
			Bolt.Angle = 0.0f;
			Bolt.Playback = 0.0f;

			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };

		}

	}

	namespace Bomb
	{


		BombBullet::BombBullet()
		{
			Bolt.Name = "Animation/SlugFile/Bomb/Bullet";
			Bolt.Duration = 0.7f;
			Bolt.Length = Vector<2>(30, 15);
			Bolt.Repeatable = true;

			Damage = 3;
			effect = new Bombeffect;
			//
			Hitbox.Name = "Image/GBB";
		}
		BombBullet::~BombBullet()
		{
			delete effect;
			effect = NULL;
		}
		void BombBullet::Start(Vector<2> location, float angle)
		{
			Damage = 3;
		
			StartLocation = location;
			Bolt.Location = location;

			Hit.Center = { Bolt.Location[0],Bolt.Location[1] };
			Hit.Length = { Bolt.Length[0],Bolt.Length[1] };
			//Demo
			Hitbox.Length = Bolt.Length;
			Hitbox.Location = Bolt.Location;

			Fly = true;
		}
		void BombBullet::Update()
		{
			if (Fly == true)
			{

				Bolt.Render();
				//Demo
				Hitbox.Render();

				Bolt.Location += Vector<2>(speed / acceleration, Bolt.Playback >= 0.3f ? -100 - gravity : 0.0f) * Engine::Time::Get::Delta();

				if (Bolt.Playback >= 0.2f) acceleration += 50 * Engine::Time::Get::Delta(), gravity += 150 * Engine::Time::Get::Delta();

				Bolt.Angle = 5 * atan((Bolt.Location[1] - StartLocation[1]) / (Bolt.Location[0] - StartLocation[0])) * (180.0f / 3.14159265f);

				Hit.Center = { Bolt.Location[0],Bolt.Location[1] };




				//Demo
				Hitbox.Location = { Bolt.Location[0],Bolt.Location[1] };
				Hitbox.Angle = Bolt.Angle;
			}
		}
		void BombBullet::End()
		{
			effect->Start(Bolt.Location);

			Bolt.Location = Vector<2>(0, 0);
			StartLocation = Vector<2>(0, 0);

			Hit.Center = { Bolt.Location[0],Bolt.Location[1]-500.0f };
		

			Bolt.Angle = 0.0f;
			Bolt.Playback = 0.0f;
			acceleration = 1.0f;
			gravity = 10.0f;
			Fly = false;
		}



		Bombeffect::Bombeffect()
		{
			effect.Name = "Animation/SlugFile/Bomb/Fire";
			effect.Duration = 1.2f;
			effect.Length = Vector<2>(150, 250);

			

			effect.Repeatable = false;
		}

		void Bombeffect::Start(Vector<2> location)
		{
			Damage = 5;
			effect.Location = { location[0],location[1] + (effect.Length[1] / 2) - 10.0f };


			Hit.Center = { effect.Location[0],effect.Location[1] };
			Hit.Length = { effect.Length[0] - 50, effect.Length[1] };

			Hitbox.Name = "Image/GBB";
			Hitbox.Location = effect.Location;
			Hitbox.Length = effect.Length - Vector<2>(50, 0);

			Check = true;
		}
		void Bombeffect::Update()
		{
			if (Check == true) effect.Render(), Hitbox.Render();

		}
		void Bombeffect::End()
		{
			if (effect.Playback >= effect.Duration)
			{
				Check = false;
				Hit.Center = { 0.0f,-500.0f };
				effect.Playback = 0.0f;
			}

		}

	}
}