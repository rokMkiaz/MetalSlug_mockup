
#include <cmath>
#include "Slug.h"





Slug::Slugarray::Slugarray()
{
	Skin.Name = "Animation/SlugFile/Body/Idle";
	Skin.Duration = 0.5f;
	Skin.Length = Vector<2>(100, 100);
	Skin.Repeatable = true;
	Skin.Location = { 200,Skin.Length[1] / 2 };

	Gun.Name = "Animation/SlugFile/Gun/HMGun";
	Gun.Duration = 1.0f;
	Gun.Repeatable = true;
	Gun.Length = Vector<2>(50, 20);
	Gun.Location = Skin.Location + Vector<2>(-30, -10);


	HMeffect.Name = "Animation/SlugFile/Gun/HMFire";
	HMeffect.Duration = 0.5f;
	HMeffect.Length = Vector<2>(40, 30);
	HMeffect.Location = Gun.Location + Vector<2>(40, 0);
	HMeffect.Repeatable = true;


	Shoteffect.Name = "Animation/SlugFile/Bomb/Shoteffect";
	Shoteffect.Duration = 1.0f;
	Shoteffect.Repeatable = true;
	Shoteffect.Length = Vector<2>(100, 70);
	Shoteffect.Location = Skin.Location + Vector<2>(70, 20);


	Hitbox.Center = { Skin.Location[0] - 5,Skin.Location[1] };
	Hitbox.Length = { Skin.Length[0] - 10.f,Skin.Length[1] };

	Invincible.Name = "Animation/SlugFile/Body/Invicible";
	Invincible.Duration = 0.2f;
	Invincible.Repeatable = true;
	Invincible.Length   ={ Hitbox.Length.x, Hitbox.Length.y };
	Invincible.Location ={ Hitbox.Center.x, Hitbox.Center.y };

	
	Hitboxprint.Name = "Image/GBB";
	//Demo
	Hitboxprint.Length   = { Hitbox.Length.x, Hitbox.Length.y };
	Hitboxprint.Location = { Hitbox.Center.x, Hitbox.Center.y };

}

void Slug::Slugarray::Moving(float const speed, Vector<2> vector)
{


	Skin.Location +=  Vector<2>(speed * vector[0], speed * vector[1]) * Engine::Time::Get::Delta();

	if (speed * vector[0] > 0 && Gun.Angle <= 180.0f && Gun.Angle >= 0.0f)
	{
		 Gun.Angle -= 150.0f * Engine::Time::Get::Delta();

	}
	else if (Gun.Angle < 0.0f)Gun.Angle = 0.0f;
	if (speed * vector[0] < 0 && Gun.Angle <= 180.0f && Gun.Angle >= 0.0f)
	{
		Gun.Angle += 150.0f * Engine::Time::Get::Delta();
	}
	else if (Gun.Angle > 180.0f)Gun.Angle = 180.0f;

	
	//Hit.Location = Skin.Location + Vector<2>(-8, 15);
	Gun.Location = Skin.Location + Vector<2>(-30, -10);

	HMeffect.Angle = Gun.Angle;
	float const radian = Gun.Angle * (3.14159265f / 180.0f);
	float const range = 40.0f;
	float x = (cos(radian) * range) + Gun.Location[0];
	float y = (sin(radian) * range) + Gun.Location[1];
	HMeffect.Location = Vector<2>(x, y);
	
	Shoteffect.Location= Skin.Location + Vector<2>(70, 20);
	
	if (invincible == false)Hitbox.Center= { Skin.Location[0] - 5,Skin.Location[1] };
	//Demo
	Hitboxprint.Location = Skin.Location - Vector<2>(5, 0);

}

void Slug::Slugarray::Rendering(SlugState state)
{
	//Demo
	Hitboxprint.Render();
	switch (state)
	{
	case SlugState::Slug_Idle:
	{
		Skin.Name = "Animation/SlugFile/Body/Idle";
		Skin.Duration = 0.5f;

		Skin.Render();
		Gun.Render();
	
		
		break;
	}
	case SlugState::Slug_Move:
	{
		Skin.Name = "Animation/SlugFile/Body/Walk";
		Skin.Duration = 1.5f;
		Skin.Length = Vector<2>(110, 100);

		Skin.Render();
		Gun.Render();

		Skin.Length = Vector<2>(100, 100);
		break;
	}
	case SlugState::Slug_Attack:
	{
		
		Skin.Name = "Animation/SlugFile/Body/Fire";
		Skin.Duration = 1.0f;

		
		

		Skin.Render();
		Shoteffect.Render();
		Gun.Render();

		
		break;
	}
	case SlugState::Slug_Hit:
	{
		Vector<2> HitLocation= Skin.Location + Vector<2>(-8, 10);
		Vector<2> Load = Skin.Location;
	

			if (Die == true)
			{
				Skin.Name = "Animation/SlugFile/Body/SlugDie";
				Skin.Length = Vector<2>(300, 300);
				Skin.Location += Vector<2>(0, +Skin.Length[1] / 2-80);
				Skin.Duration = 2.0f;
				Skin.Repeatable = false;

			}
			else
			{
				Skin.Name = "Animation/SlugFile/Body/Hit";
				Skin.Duration = 0.9f;
				Skin.Length = Vector<2>(140, 120);
				Skin.Location = HitLocation;
			}
			

			

		Skin.Render();
		if(Die==false)Gun.Render();
		Skin.Length = Vector<2>(100, 100);
		Skin.Location = Load;



		break;
	}
	case SlugState::Slug_HMFire:
	{
		HMeffect.Render();
		if (invincible == true)Invincible.Render();
		
		
		break;
		
	}
	case SlugState::Slug_Invincible:
	{
		Invincible.Length =    { Skin.Length[0] - 10.f, Skin.Length[1] };
		Invincible.Location = { Skin.Location[0] - 5,Skin.Location[1] };

		InvincibleTime += Engine::Time::Get::Delta();
		if(InvincibleTime >1.5f) invincible = false, InvincibleTime=0.0f, Hitbox.Center = { Skin.Location[0] - 5,Skin.Location[1] };
		else Hitbox.Center = { Skin.Location[0],Skin.Location[1] -300 };

		Invincible.Render();
		break;
	}
	}
	
	
}



void Slug::Start()
{


	Slugbody = new Slugarray;
	
	Hp = 10;
	for (int i = 0; i < BulletNum + 1; i++)
	{
		bullet2[i] = &hmbullet[i];
	}
	bullet1 = &BBbullet;
	Actorphysics = Slugbody->Hitbox;
	
	Look = &Slugcam;
	Slugcam.Start();
	

}

void Slug::Update()
{
	
	if (Slugbody->Skin.Location[0] < 2850.f && Slugbody->Skin.Location[0] >  (BossStage == true ? 2300.f : 100.f))
	{
		if (Slugbody->Skin.Location[0] > 2500.f)BossStage = true;

		if ((Engine::Input::Get::Key::Press('A') || Engine::Input::Get::Key::Press('D') || Engine::Input::Get::Key::Down('J')) && Attackmotion == false && Hitmotion == false && Slugbody->Die == false)
		{
			if (Engine::Input::Get::Key::Press('A'))
			{
				Slugbody->Moving(speed, Vector<2>(-1, 0)), Slugbody->Rendering(Slug_Move);
				if (Slugbody->invincible == true)Slugbody->Rendering(Slug_Invincible);
			}
			if (Engine::Input::Get::Key::Press('D'))
			{
				Slugbody->Moving(speed, Vector<2>(1, 0)), Slugbody->Rendering(Slug_Move);
				if (Slugbody->invincible == true)Slugbody->Rendering(Slug_Invincible);
			}
			if (Engine::Input::Get::Key::Down('J') )
			{
				Slugbody->Skin.Playback = 0.1f, Attackmotion = true, BBbullet.Start(Slugbody->BombLocation() - Vector<2>(0, 10), 0.0f);
				
			}

		}
		else if (Hitmotion == true )
		{
			if (Hp <= 0)Slugbody->Die = true, Hitmotion = true;
			else Slugbody->invincible = true;
			Slugbody->Rendering(Slug_Hit);
			Slugbody->Rendering(Slug_Invincible);
			if (Slugbody->Skin.Playback > 0.7f)Hitmotion = false;

		}

		else if (Attackmotion == false && Slugbody->Die!=true)
		{
			Slugbody->Rendering(Slug_Idle);
			if (Slugbody->invincible == true)Slugbody->Rendering(Slug_Invincible);
		}
	}
	else if (Slugbody->Skin.Location[0] >= 2850.f)Slugbody->Moving(speed , Vector<2>(-1, 0)), Slugbody->Rendering(Slug_Move);
	else if (Slugbody->Skin.Location[0] <= (BossStage == true ? 2300.f : 100.f))Slugbody->Moving(speed, Vector<2>(1, 0)), Slugbody->Rendering(Slug_Move);


	if (Attackmotion == true && Slugbody->Die!=true )
	{
		if (Slugbody->invincible == true)Slugbody->Rendering(Slug_Invincible);
		BBbullet.Update();
		if(Hitmotion != true)Slugbody->Rendering(Slug_Attack);
		bullet1->Update();

		if (Slugbody->Skin.Playback > 0.98f)Attackmotion = false,Slugbody->Shoteffect.Playback=0.0f;
	}


	if (Engine::Input::Get::Key::Press('K') && Slugbody->Die ==false )
	{	
		float cooldown = 0.15f;
		if (hmbullet[Fire].Fly == false)hmbullet[Fire].Start(Slugbody->HMGunLocation() + Vector<2>(0, Fire % 2 == 0 ? +5 : (Fire % 3 == 0 ? -5 : 0)), Slugbody->HMGunAngle());
		
	
		delay += 1*Engine::Time::Get::Delta();

		if (delay >= cooldown)Fire++, delay = 0.0f; 
		if (Fire > BulletNum)Fire = 0;
		

		Slugbody->Rendering(Slug_HMFire);
		

	}

	for (int i = 0; i <= BulletNum; i++)
	{
		hmbullet[i].Update();

		if (sqrt(powf(hmbullet[i].Bolt.Location[0]-Slugbody->Gun.Location[0], 2) + powf(hmbullet[i].Bolt.Location[1]- Slugbody->Gun.Location[1], 2)) >  1000.f ) hmbullet[i].End();
	}

	Actorphysics = Slugbody->Hitbox;

	 
	if (Slugbody->Skin.Location[0] > 700.f && Slugbody->Skin.Location[0] < 2700.f)Slugcam.cam.Location = Slugbody->Skin.Location + Vector<2>(0, 200), Slugcam.Update();

	Look = &Slugcam;
}

void Slug::End()
{

		
	delete Slugbody;
}

float Slug::Location()
{
	return Slugbody->Skin.Location[0];
}


