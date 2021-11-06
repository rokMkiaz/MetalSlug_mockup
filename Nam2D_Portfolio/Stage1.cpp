#include "Engine\Rendering.h"
#include "Stage1.h"


#include "Slug.h"
#include"SlugBullet.h"
#include "Enemy.h"
#include "Boss.h"

Stage1::Stage1()
{
	Map.Name = "Image/Stage1";
	Map.Length = Vector<2>(3800, 720);
	Map.Location = Vector<2>(1400, 300);

	Ground.Center = { Map.Location[0],-50.0f };
	Ground.Length = { Map.Length[0], 100.f };

	Groundphysics.Name = "Image/RBB";
	Groundphysics.Location = { Map.Location[0]+200, -50.0f };
	Groundphysics.Length= { Map.Length[0] , 100.f };


	
}

void Stage1::Start()
{
	Player = new Slug;
	for (int i = 0; i < 40; i++)
	{
		EnemySoldier[i] = new Enemy::Soldier::Soldier;
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyTank[i] = new Enemy::Tank::Tank;
	}

	Boss = new Enemy::Boss;

	Player->Start();
	for (int i = 0; i < 40; i++)
	{
		EnemySoldier[i]->Start();
		EnemySoldier[i]->Target(Player);
		EnemySoldier[i]->SelectLocation(Vector<2>(-1000, 0));
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyTank[i]->Start();
		EnemyTank[i]->Target(Player);
		EnemyTank[i]->SelectLocation(Vector<2>(-1000, 0));
	}
	 
	Boss->Start();
	Boss->Target(Player);
	Boss->SelectLocation(Vector<2>(3060, 0));

	stageCam1.Start();
	stageCam2.Start();

	
}

Stage* Stage1::Update()
{
	Map.Render();
	if (Player->Location() <= 700.f)	stageCam1.cam.Set();
	if(Player->Location() >= 2700.f)	stageCam2.cam.Set();
	/*
	if (Engine::Input::Get::Key::Press('P'))
	{
		
		for (int i = 0; i < 20; i++)
		{
			EnemySoldier[i]->Start();
			EnemySoldier[i]->SelectLocation(Vector<2>(800 + (i % 3 == 0 ? i * 10 : i % 2 == 0 ? 0 : i * -10)    , 0));
		}
		for (int i = 0; i < 5; i++)
		{
			EnemyTank[i]->Start();
			EnemyTank[i]->Target(Player);
			EnemyTank[i]->SelectLocation(Vector<2>(800 + (i* 50),0));
		}
		Boss->SelectLocation(Vector<2>(1000, 0));
	}
	*/
	//Wave1
	if (Player->Location() >= 600.f ) Wavve1 = true;
	if(Wavve1==true && Count==0)
	{

		for (int i = 0; i < 5; i++)
		{
			EnemySoldier[i]->Start();
			EnemySoldier[i]->SelectLocation(Vector<2>((Player->Location()+800.f) + (i % 3 == 0 ? i * 10 : i % 2 == 0 ? 0 : i * -10), 0));
		}
		for (int i = 5; i < 10; i++)
		{
			EnemySoldier[i]->Start();
			EnemySoldier[i]->SelectLocation(Vector<2>((Player->Location() - 600.f) - (i % 3 == 0 ? i * 10 : i % 2 == 0 ? 0 : i * -10), 0));
		}
		
		for (int i = 0; i < 2; i++)
		{
			EnemyTank[i]->Start();
			EnemyTank[i]->SelectLocation(Vector<2>((Player->Location() + 800.f) + (i * 100), 0));
		}
		
			Wavve1 = false;
			Count++;
		
	}
	//Wave2
	if (Player->Location() >= 1000.f) Wavve2 = true;
	if (Wavve2 == true && Count == 1)
	{

		for (int i = 10; i < 15; i++)
		{
			EnemySoldier[i]->Start();
			EnemySoldier[i]->SelectLocation(Vector<2>((Player->Location() + 800.f) + (i % 3 == 0 ? i * 10 : i % 2 == 0 ? 0 : i * -10), 0));
		}
		for (int i = 15; i < 20; i++)
		{
			EnemySoldier[i]->Start();
			EnemySoldier[i]->SelectLocation(Vector<2>((Player->Location() - 750.f) - (i % 3 == 0 ? i * 10 : i % 2 == 0 ? 0 : i * -10), 0));
		}

		for (int i = 2; i < 5; i++)
		{
			EnemyTank[i]->Start();
			EnemyTank[i]->SelectLocation(Vector<2>((Player->Location() + 800.f)+(i%2? i*50:i*-50)  , 0));
		}

		Wavve2 = false;
		Count++;

	}
	//Wave3
	if (Player->Location() >= 1800.f)Wavve3 = true;
	if(Wavve3==true && Count==2)
	{

		for (int i = 20; i < 30; i++)
		{
			EnemySoldier[i]->Start();
			EnemySoldier[i]->SelectLocation(Vector<2>((Player->Location() + 800.f) + (i % 3 == 0 ? i * 10 : i % 2 == 0 ? 0 : i  * -10), 0));
		}
		for (int i = 30; i < 40; i++)
		{
			EnemySoldier[i]->Start();
			EnemySoldier[i]->SelectLocation(Vector<2>((Player->Location() - 750.f) + (i  % 3 == 0 ? i  * 10 : i % 2 == 0 ? 0 : i  * -10), 0));
		}
		for (int i = 5; i < 10; i++)
		{
			EnemyTank[i]->Start();
			EnemyTank[i]->SelectLocation(Vector<2>((Player->Location() + 800.f) - (i%2==0? (i-5)* 50:(i-5)*-50), 0));
		}
		Wavve3 = false;
		Count++;
	
	}
	//BossStage
	if (Player->Location() >= 2500.f)BossStage = true;
	if (BossStage == true && Count == 3 && Boss->Hp>0)
	{
			static int Regen = 0;
		
	
			EnemySoldier[Regen]->Start();
			EnemySoldier[Regen]->SelectLocation(Vector<2>((Player->Location() - 800.f) + (Regen % 3 == 0 ? Regen * 10 : Regen % 2 == 0 ? 0 : Regen * -10), 0));
		

			BossStageTime += Engine::Time::Get::Delta();

			if (BossStageTime > 3.0f)Regen++, BossStageTime=0.0f;
			if (Regen > 19)Regen = 0;


	}

	
	
	if (Player->bullet1->Hit.Collide(Ground) && Player->bullet1->Fly == true)
	{
		if (Player->bullet1->effect->Check == true)
		{
			Player->bullet1->effect = new SlugBullet::Bomb::Bombeffect;

		}
	
	
		Player->bullet1->End();
	}

	//EnemySoldier
	for (int i = 0; i < 40; i++)
	{
		
		if (Player->bullet1->effect->Hit.Collide(EnemySoldier[i]->Actorphysics) && EnemySoldier[i]->Hp > 0)
		{
		
		
			EnemySoldier[i]->Deathmotion(3);
		    EnemySoldier[i]->Hp -= Player->bullet1 ->effect->Damage ;
			//Player->bullet1->effect->Damage = 0;//Start에서 데미지를 넣어줌으로써 연속 충돌 해결,  보병들상대로는 상관없게함.
		
		
		}
	
		if (Player->bullet1->Hit.Collide(EnemySoldier[i]->Actorphysics) && EnemySoldier[i]->Hp > 0)
		{
			
			if (Player->bullet1->effect->Check == true)
			{
				Player->bullet1->effect = new SlugBullet::Bomb::Bombeffect;

			}
			
		

			Player->bullet1->End();
			EnemySoldier[i]->Deathmotion(3);
			//EnemySoldier[i]->Hp -= Player->bullet1->Damage;
		}

		if (EnemySoldier[i]->bullet1->Hit.Collide(Ground) && EnemySoldier[i]->bullet1->Fly==true)
		{
			EnemySoldier[i]->bullet1->End();
		}
		if (EnemySoldier[i]->bullet1->Hit.Collide(Player->Actorphysics))
		{
			

			Player->Hp -= EnemySoldier[i]->bullet1->Damage;
			Player->Deathmotion(1);
			EnemySoldier[i]->bullet1->End();
			
		}
	}
	//EnemyTank
	for (int i = 0; i < 10; i++)
	{

		if (Player->bullet1->effect->Hit.Collide(EnemyTank[i]->Actorphysics) && EnemyTank[i]->Hp > 0)
		{


			EnemyTank[i]->Deathmotion(3);
			EnemyTank[i]->Hp -= Player->bullet1->effect->Damage;
			Player->bullet1->effect->Damage = 0;//Start에서 데미지를 넣어줌으로써 연속 충돌 해결,  보병들상대로는 상관없게함.


		}

		if (Player->bullet1->Hit.Collide(EnemyTank[i]->Actorphysics) && EnemyTank[i]->Hp > 0)
		{

			if (Player->bullet1->effect->Check == true)
			{
				Player->bullet1->effect = new SlugBullet::Bomb::Bombeffect;

			}



			Player->bullet1->End();
			EnemyTank[i]->Deathmotion(3);
			//EnemySoldier[i]->Hp -= Player->bullet1->Damage;
		}

		if (EnemyTank[i]->bullet1->Hit.Collide(Ground) && EnemyTank[i]->bullet1->Fly == true)
		{
			EnemyTank[i]->bullet1->End();
		}
		if (EnemyTank[i]->bullet1->Hit.Collide(Player->Actorphysics))
		{


			Player->Hp -= EnemyTank[i]->bullet1->Damage;
			Player->Deathmotion(1);
			EnemyTank[i]->bullet1->End();

		}
		if (Player->Actorphysics.Collide(EnemyTank[i]->Actorphysics))//탱크 충돌시 홀딩
		{
			EnemyTank[i]->Hp = 0;
			Player->Deathmotion(1);
		}

	}

	//Boss
	if (Player->bullet1->effect->Hit.Collide(Boss->Actorphysics) && Boss->Hp > 0)
	{

	
		Boss->Hp -= Player->bullet1->effect->Damage;
		Player->bullet1->effect->Damage = 0;//Start에서 데미지를 넣어줌으로써 연속 충돌 해결

	}

	if (Player->bullet1->Hit.Collide(Boss->Actorphysics) && Boss->Hp > 0)
	{

		if (Player->bullet1->effect->Check == true)
		{
			Player->bullet1->effect = new SlugBullet::Bomb::Bombeffect;

		}

		Player->bullet1->End();
	
		//EnemySoldier[i]->Hp -= Player->bullet1->Damage;
	}

	if (Boss->bullet1->Hit.Collide(Ground) && Boss->bullet1->Fly == true)
	{
		Boss->bullet1->End();
	}
	if (Boss->bullet1->Hit.Collide(Player->Actorphysics))
	{


		Player->Hp -= Boss->bullet1->Damage;
		Player->Deathmotion(1);
		Boss->bullet1->End();

	}
	//Boss Sub attack Test
	for (int i = 0; i < 9; i++)
	{
		if (Boss->bullet2[i]->Hit.Collide(Ground) && Boss->bullet2[i]->Fly == true)
		{
			Boss->bullet2[i]->End();
		}
		if (Boss->bullet2[i]->Hit.Collide(Player->Actorphysics))
		{
			Player->Hp -= Boss->bullet2[i]->Damage;
			Player->Deathmotion(1);
			Boss->bullet2[i]->End();
		}
		for (int j = 0; j < 15; j++)
		{
			if (Player->bullet2[j]->Hit.Collide(Boss->bullet2[i]->Hit) && Player->bullet2[j]->Fly==true)
			{
				{
					Boss->bullet2[i]->End();
					Player->bullet2[j]->End();
					Player->bullet2[j]->Damage = 0;
				}
			}
		}
	}


	static int Random = 4;
	for (int j = 0; j < 40; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			if (Player->bullet2[i]->Hit.Collide(EnemySoldier[j]->Actorphysics) && EnemySoldier[j]->Hp > 0)
			{
				EnemySoldier[j]->Deathmotion(Random);
				Player->bullet2[i]->End(), EnemySoldier[j]->Hp -= Player->bullet2[i]->Damage;
				Player->bullet2[i]->Damage=0;
			}
		}
	}
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			if (Player->bullet2[i]->Hit.Collide(EnemyTank[j]->Actorphysics) && EnemyTank[j]->Hp > 0)
			{
				
				Player->bullet2[i]->End(), EnemyTank[j]->Hp -= Player->bullet2[i]->Damage;
				Player->bullet2[i]->Damage = 0;
			}
		}
	}

	for (int i = 0; i < 15; i++)
	{
		if (Player->bullet2[i]->Hit.Collide(Boss->Actorphysics) && Boss->Hp > 0)
		{
			Player->bullet2[i]->End(), Boss->Hp -= Player->bullet2[i]->Damage;
			Player->bullet2[i]->Damage = 0;
		}
	}


	Random++;
	if (Random > 6)Random = 4;
	

	
	
	Groundphysics.Render();

	//DEMO
	
	for (int i = 0; i < 40; i++)
	{
		EnemySoldier[i]->Update();
		EnemySoldier[i]->bullet1->effect->Update();
		EnemySoldier[i]->bullet1->effect->End();
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyTank[i]->Update();
		EnemyTank[i]->bullet1->effect->Update();
		EnemyTank[i]->bullet1->effect->End();
	}

	Boss->bullet1->effect->Update();
	Boss->bullet1->effect->End();
	Boss->Update();
	for (int i = 0; i < 9; i++)
	{
		Boss->bullet2[i]->effect->Update();
		Boss->bullet2[i]->effect->End();
	}
	Player->bullet1->effect->Update();
	Player->bullet1->effect->End();
	
	Player->Update();

	return nullptr;
}

void Stage1::End()
{
	
	Player->End();
	
	for (int i = 0; i < 40; i++)
	{
		EnemySoldier[i]->End();
		delete[] EnemySoldier[i];
	}
	for (int i = 0; i < 10; i++)
	{
		EnemyTank[i]->End();
		delete[] EnemyTank[i];
	}

	//delete effect;
	delete Player;
}
