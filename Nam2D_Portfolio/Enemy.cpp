#include<cmath>


#include "Enemy.h"
#include"Engine\Physics.h"
#include"Effect.h"



#include"Engine\Input.h"
#include"Engine\Time.h"

namespace Enemy
{

	namespace Soldier
	{
		Soldier::Soldierarray::Soldierarray()
		{
			

			Skin.Name = "Animation/Enemy/Soldier/Idle";
			Skin.Duration = 0.5f;
			Skin.Length = Vector<2>(60, 70);
			Skin.Location = Vector<2>(0.0f, Skin.Length[1] / 2);
			Skin.Repeatable = true;

			Hitbox.Center = { Skin.Location[0], Skin.Location[1] };
			Hitbox.Length = { Skin.Length[0]-20,Skin.Length[1]-5 };

			Search.Center= { Skin.Location[0], Skin.Location[1] };
			Search.Length = { Skin.Length[0] +1100,Skin.Length[1]+1100 };


			//Demo
			Hitboxprint.Name = "Image/GBB";
			Hitboxprint.Location = { Skin.Location[0], Skin.Location[1] };
			Hitboxprint.Length = { Skin.Length[0] - 20,Skin.Length[1]-5 };

		}

		void Soldier::Soldierarray::Moving(float const speed, Vector<2> vector)
		{
			Skin.Location += { vector[0] * speed* Engine::Time::Get::Delta(), vector[1] * speed* Engine::Time::Get::Delta() };
			Hitbox.Center = { Skin.Location[0], Skin.Location[1] };
			Search.Center = { Skin.Location[0], Skin.Location[1] };


			Hitboxprint.Location = { Skin.Location[0],Skin.Location[1] };

		}

		void Soldier::Soldierarray::Rendering(EnemyState state)
		{
			//Demo
			Hitboxprint.Render();
			switch (state)
			{
			case EnemyState::Enemy_Idle:
			{
				Skin.Name = "Animation/Enemy/Soldier/Idle";
				//Skin.Duration = 1.0f;

				Skin.Render();
				break;
			}
			case EnemyState::Enemy_Move:
			{
			
				Skin.Name = "Animation/Enemy/Soldier/Walk";
				Skin.Duration = 0.7f;
				Skin.Length = Vector<2>(70, 75);
				Skin.Location = Vector<2>(Skin.Location[0] + 5, Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(60, 70);
				Skin.Location = Vector<2>(Skin.Location[0] - 5, Skin.Length[1] / 2);

				break;
			}
			case EnemyState::Enemy_Attack:
			{
				Skin.Name = "Animation/Enemy/Soldier/Attack";
				Skin.Duration = 0.5f;
				Skin.Length = Vector<2>(75, 83);
				Skin.Location = Vector<2>(Skin.Location[0]+5, Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(60, 70);
				Skin.Location = Vector<2>(Skin.Location[0]-5, Skin.Length[1] / 2);
				break;
			}
			case EnemyState::Enemy_BombHit:
			{
				
				Skin.Name = "Animation/Enemy/Soldier/Firedeath";
				Skin.Duration = 1.2f;
				Skin.Length = Vector<2>(90, 110);
				Skin.Location = Vector<2>(Skin.Location[0], Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(60, 70);
				Skin.Location = Vector<2>(Skin.Location[0], Skin.Length[1] / 2);
				break;
			}
			case EnemyState::Enemy_Hit1:
			{

				Skin.Name = "Animation/Enemy/Soldier/Death1";
				Skin.Duration = 0.7f;
				Skin.Length = Vector<2>(70, 75);
				Skin.Location = Vector<2>(Skin.Location[0]+5, Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(60, 70);
				Skin.Location = Vector<2>(Skin.Location[0] - 5, Skin.Length[1] / 2);
				break;
			}
			case EnemyState::Enemy_Hit2:
			{

				Skin.Name = "Animation/Enemy/Soldier/Death2";
				Skin.Duration = 0.5f;
				Skin.Length = Vector<2>(90, 75);
				Skin.Location = Vector<2>(Skin.Location[0] + 5, Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(60, 70);
				Skin.Location = Vector<2>(Skin.Location[0] - 5, Skin.Length[1] / 2);
				break;
			}
			case EnemyState::Enemy_Hit3:
			{

				Skin.Name = "Animation/Enemy/Soldier/Death3";
				Skin.Duration = 0.7f;
				Skin.Length = Vector<2>(70, 75);
				Skin.Location = Vector<2>(Skin.Location[0] + 5, Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(60, 70);
				Skin.Location = Vector<2>(Skin.Location[0] - 5, Skin.Length[1] / 2);
				break;
			}
			}
		}


		Soldier::~Soldier()
		{
			delete Soldierbody;
			Soldierbody = NULL;
		}

		void Soldier::Start()
		{
			Soldierbody = new Soldierarray;
			Hp = 3;
			Actorphysics = Soldierbody->Hitbox;

			bullet1 = &Bomb;
			

		}

		void Soldier::Update()
		{
			RandFire += 1.0f* Engine::Time::Get::Delta();

			if (Hp <= 0 ) //Death
			{
				Hp = 0;
				if (Hp == 0 && Motion ==false)Motion = true, Soldierbody->Skin.Playback=0.0f;
			
				AttackMotion = false;
				float time = Soldierbody->Skin.Playback;
				
				Soldierbody->Rendering(static_cast<EnemyState>(DieMotion));

				if (time + 0.1f > Soldierbody->Skin.Duration )End(),Motion=false;

			}
			else if(Hp>0)
			{
		
				float const Range     = Soldierbody->Skin.Location[0] - PlayerTarget->Location();

				if (Range < 0)Soldierbody->Skin.Flipped = true;
				else Soldierbody->Skin.Flipped = false;
		
				if (Soldierbody->Search.Collide(PlayerTarget->Actorphysics) && Soldierbody->Skin.Flipped == false ? Range > 200.f: Range < -200.f)
				{
					if (Soldierbody->Skin.Flipped == false && AttackMotion == false)Soldierbody->Rendering(Enemy_Move), Soldierbody->Moving(speed, Vector<2>(-1, 0));
					else if (Soldierbody->Skin.Flipped == true && AttackMotion == false)Soldierbody->Rendering(Enemy_Move),Soldierbody->Moving(speed*1.5f, Vector<2>(1, 0));


				}
				else if(AttackMotion == false) Soldierbody->Rendering(Enemy_Idle);
				if (AttackMotion == true && Bomb.Fly == true)
				{
				
					if (Bomb.Bolt.Playback < 1.1f)Soldierbody->Rendering(Enemy_Attack);
					else Soldierbody->Rendering(Enemy_Idle);
				}


				if (abs(Range) <= abs(RandFire*1.2) * 100.0f && AttackMotion != true && abs(Range)>200.f)
				{
					AttackMotion = true;
					Soldierbody->Skin.Playback = 0.0f;
					Bomb.Start(Soldierbody->Skin.Location, 5.0f+(RandFire *10));
					
					Bomb.Fly = true;
				}
				
				if (AttackMotion == true)
				{
					if (Bomb.Fly==false)AttackMotion = false;
				}

			}

		

			if (RandFire >= 6.0f)RandFire = 2.0f;




		
			if(Bomb.Fly==true)
			{
				if (Soldierbody->Skin.Flipped == false )Bomb.Update();
				else Bomb.speed*=-1 , Bomb.Update(),Bomb.speed *= -1;
			}
			
		

			Actorphysics = Soldierbody->Hitbox;
		}

		void Soldier::End()
		{
			

			Soldierbody->Skin.Location = Vector<2>(-100, 0);

			Soldierbody->Hitbox.Center = { Soldierbody->Skin.Location[0],Soldierbody->Skin.Location[1] };
			Soldierbody->Search.Center = { Soldierbody->Skin.Location[0], Soldierbody->Skin.Location[1] };
			Soldierbody->Hitboxprint.Location = { Soldierbody->Skin.Location[0],Soldierbody->Skin.Location[1] };


			Soldierbody->Skin.Playback = 0.0f;
			
			Actorphysics = Engine::Physics::Component<Quadrangle>() ;
	
			
			
		}


		void Soldier::SelectLocation(Vector<2> location)
		{
		

			Soldierbody->Skin.Location = { location[0], Soldierbody->Skin.Location[1] };
			Soldierbody->Hitbox.Center = { Soldierbody->Skin.Location[0], Soldierbody->Skin.Location[1] };
			Soldierbody->Search.Center = { Soldierbody->Skin.Location[0], Soldierbody->Skin.Location[1] };


			Soldierbody->Hitboxprint.Location = { Soldierbody->Skin.Location[0],Soldierbody->Skin.Location[1] };
		}
	}

	namespace Tank
	{
		Tank::Tankarray::Tankarray()
		{
			Skin.Name = "Animation/Enemy/Tank/Idle";
			Skin.Duration = 0.2f;
			Skin.Length = Vector<2>(120, 100);
			Skin.Location = Vector<2>(0.0f, Skin.Length[1] / 2);
			Skin.Repeatable = true;

			

		    FireEffect.Name = "Animation/Enemy/Tank/Shoteffect";
			FireEffect.Duration = 1.0f;
			FireEffect.Repeatable = true;
			FireEffect.Flipped = true;
			FireEffect.Length = Vector<2>(100, 80);
			FireEffect.Location = Skin.Location + Vector<2>(-65, 60);
			FireEffect.Angle = -30.0f;




			Hitbox.Center = { Skin.Location[0], Skin.Location[1] };
			Hitbox.Length = { Skin.Length[0] - 20,Skin.Length[1] - 5 };

			Search.Center = { Skin.Location[0], Skin.Location[1] };
			Search.Length = { Skin.Length[0] + 1100,Skin.Length[1] + 1100 };


			//Demo
			Hitboxprint.Name = "Image/GBB";
			Hitboxprint.Location = { Skin.Location[0], Skin.Location[1] };
			Hitboxprint.Length = { Skin.Length[0] - 20,Skin.Length[1] - 5 };

		}
		void Tank::Tankarray::Moving(float const speed, Vector<2> vector)
		{
			Skin.Location += { vector[0] * speed* Engine::Time::Get::Delta(), vector[1] * speed* Engine::Time::Get::Delta() };
			Hitbox.Center = { Skin.Location[0], Skin.Location[1] };
			Search.Center = { Skin.Location[0], Skin.Location[1] };

			FireEffect.Location = Skin.Location + Vector<2>(-65, 60);
		
			
			Hitboxprint.Location = { Skin.Location[0],Skin.Location[1] };
		}
		void Tank::Tankarray::Rendering(EnemyState state)
		{
			//Demo
			Hitboxprint.Render();
			switch (state)
			{
			case EnemyState::Enemy_Idle:
			{
				Skin.Name = "Animation/Enemy/Tank/Idle";
				Skin.Duration = 0.2f;

				Skin.Render();
				break;
			}
			case EnemyState::Enemy_Move:
			{

				Skin.Name = "Animation/Enemy/Tank/Walk";
				Skin.Duration = 0.5f;
				Skin.Length = Vector<2>(120, 100);
				Skin.Location = Vector<2>(Skin.Location[0] + 5, Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(120, 100);
				Skin.Location = Vector<2>(Skin.Location[0] - 5, Skin.Length[1] / 2);

				break;
			}
			case EnemyState::Enemy_Attack:
			{
				Skin.Name = "Animation/Enemy/Tank/Shot";
				Skin.Duration = 1.0f;
				Skin.Length = Vector<2>(120, 100);
				Skin.Location = Vector<2>(Skin.Location[0] + 5, Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(120, 100);
				Skin.Location = Vector<2>(Skin.Location[0] - 5, Skin.Length[1] / 2);
				break;
			}
			case EnemyState::Enemy_BombHit:
			{

				if(Skin.Playback<0.5f)Skin.Name = "Animation/Enemy/Tank/Death", Skin.Length = Vector<2>(140, 120);
				else Skin.Name = "Animation/Enemy/Tank/Fire", Skin.Length = Vector<2>(150, 250);
				Skin.Duration = 1.2f;
				
				Skin.Location = Vector<2>(Skin.Location[0], Skin.Length[1] / 2);


				Skin.Render();
				Skin.Length = Vector<2>(120, 100);
				Skin.Location = Vector<2>(Skin.Location[0], Skin.Length[1] / 2);
				break;
			}
	
			}

		}

		Tank::~Tank()
		{
			delete Tankbody;
			Tankbody = NULL;
		}

		void Tank::Start()
		{
			Tankbody = new Tankarray;
			Hp = 30;
			Actorphysics = Tankbody->Hitbox;

			bullet1 = &Bomb;
		}
		void Tank::Update()
		{
			RandFire += 1.0f * Engine::Time::Get::Delta();
			
			if (Hp <= 0) //Death
			{
				Hp = 0;
				if (Hp == 0 && Motion == false)Motion = true, Tankbody->Skin.Playback = 0.0f;

				AttackMotion = false;
				float time = Tankbody->Skin.Playback;

				Tankbody->Rendering(static_cast<EnemyState>(DieMotion));

				if (time + 0.1f > Tankbody->Skin.Duration)End(), Motion = false;

			}
			else if (Hp > 0)
			{

				float const Range = Tankbody->Skin.Location[0] - PlayerTarget->Location();

			
			
				if (Tankbody->Search.Collide(PlayerTarget->Actorphysics) &&  (Range > 200.f || Range < -200.f))
				{
					if (Range > 200.f && AttackMotion == false)Tankbody->Rendering(Enemy_Move), Tankbody->Moving(speed, Vector<2>(-1, 0));
					else if (Range < -200.f && AttackMotion == false)Tankbody->Rendering(Enemy_Move), Tankbody->Moving(speed, Vector<2>(1, 0));
				

				}
				else if (AttackMotion == false) Tankbody->Rendering(Enemy_Idle);
				if (AttackMotion == true && Bomb.Fly == true)
				{

					if (Bomb.Bolt.Playback < 1.0f)Tankbody->Rendering(Enemy_Attack),Tankbody->FireEffect.Render();
					else Tankbody->Rendering(Enemy_Idle);
				}


				if (Range <= RandFire * 150.0f && AttackMotion != true && Range > 200.f)
				{
					AttackMotion = true;
					Tankbody->Skin.Playback = 0.0f;
					Bomb.Start(Tankbody->FireEffect.Location, 10.0f + (RandFire * 10.0f));

					Bomb.Fly = true;


				}

				if (AttackMotion == true)
				{
					if (Bomb.Fly == false)AttackMotion = false;
				}

			}

			
			if (RandFire >= 6.0f)RandFire = 2.0f;





			if (Bomb.Fly == true)
			{
				Bomb.Update();
			
			}



			Actorphysics = Tankbody->Hitbox;
		}
		
		void Tank::End()
		{

			Tankbody->Skin.Location = Vector<2>(-100, 0);

			Tankbody->Hitbox.Center = { Tankbody->Skin.Location[0], Tankbody->Skin.Location[1] };
			Tankbody->Search.Center = { Tankbody->Skin.Location[0], Tankbody->Skin.Location[1] };
			Tankbody->Hitboxprint.Location = { Tankbody->Skin.Location[0],Tankbody->Skin.Location[1] };


			Tankbody->Skin.Playback = 0.0f;

			Actorphysics = Engine::Physics::Component<Quadrangle>();
		}
	
	
		void Tank::SelectLocation(Vector<2> location)
		{
			Tankbody->Skin.Location = { location[0], Tankbody->Skin.Location[1] };
			Tankbody->Hitbox.Center = { Tankbody->Skin.Location[0], Tankbody->Skin.Location[1] };
			Tankbody->Search.Center = { Tankbody->Skin.Location[0], Tankbody->Skin.Location[1] };


			Tankbody->Hitboxprint.Location = { Tankbody->Skin.Location[0],Tankbody->Skin.Location[1] };
		}
	}

}