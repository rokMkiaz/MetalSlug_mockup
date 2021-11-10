
#include "Boss.h"
#include"Engine\Time.h"
//Test 
#include"Engine\Input.h"

namespace Enemy
{
    Boss::Bossarray::Bossarray()
    {
       Body[0].Name = "Animation/Enemy/Boss/Mainbody/Secondfloor";
       Body[0].Duration = 0.8f;
       Body[0].Length = Vector<2>(300, 200);
       Body[0].Location = Vector<2>(600, Body[0].Length[1] / 2);
       Body[0].Repeatable = true;

       Body[1].Name = "Animation/Enemy/Boss/Mainbody/Body1";
       Body[1].Duration = 0.8f;
       Body[1].Length = Vector<2>(300, 100);
       Body[1].Location = Body[0].Location+Vector<2>(0,Body[0].Length[1]/2-30) + Vector<2>(0, Body[1].Length[1] / 2);
       Body[1].Repeatable = true;

       Body[2].Name = "Animation/Enemy/Boss/Mainbody/Body2";
       Body[2].Duration = 0.8f;
       Body[2].Length = Vector<2>(220, 50);
       Body[2].Location = Body[1].Location + Vector<2>(0, 5) + Vector<2>(0, Body[1].Length[1] / 2);
       Body[2].Repeatable = true;

       //Cap
       Cap[0].Name = "Animation/Enemy/Boss/Mainbody/Cap1";
       Cap[0].Duration = 1.0f;
       Cap[0].Length = Vector<2>(200, 280);
       Cap[0].Repeatable = true;

       Cap[1].Name = "Animation/Enemy/Boss/Mainbody/Cap2";
       Cap[1].Duration = 1.0f;
       Cap[1].Length = Vector<2>(200, 280);
       Cap[1].Repeatable = true;

       Cap[2].Name = "Animation/Enemy/Boss/Mainbody/Cap3";
       Cap[2].Duration = 1.0f;
       Cap[2].Length = Vector<2>(200, 280);
       Cap[2].Repeatable = true;


        Hitbox[0].Center = { Body[0].Location[0], Body[0].Location[1] };
        Hitbox[0].Length = { Body[0].Length[0] ,Body[0].Length[1] };

        //MainWeapon
        MainGun.Name = "Animation/Enemy/Boss/Mainweapon/Idle";
        MainGun.Duration = 2.0f;
        MainGun.Length = Vector<2>(220, 250);
        MainGun.Location = Body[1].Location + Vector<2>(0, -5) + Vector<2>(0, MainGun.Length[1] / 2);
        MainGun.Repeatable = true;

        MainEffect.Name= "Animation/Enemy/Boss/Mainweapon/Fireeffect";
        MainEffect.Duration = 1.5f;
        MainEffect.Length = Vector<2>(150, 150);
        MainEffect.Repeatable = true;
      

        //SubWeapon
        SubGun.Name= "Animation/Enemy/Boss/Subweapon/SubIdle";
        SubGun.Location = Body[1].Location + Vector<2>(-50, 0);
        SubGun.Duration = 0.5f;
        SubGun.Length= Vector<2>(90, 68);
        SubGun.Repeatable = true;

        SubEffect.Name = "Animation/Enemy/Boss/Subweapon/SubEffect";
        SubEffect.Location = SubGun.Location + Vector<2>(0,20);
        SubEffect.Duration = 0.7f;
        SubEffect.Length = Vector<2>(90, 68);
        SubEffect.Repeatable = true;
        
        Search.Center = { MainGun.Location[0], MainGun.Location[1] };
        Search.Length = { MainGun.Length[0] + 1500,MainGun.Length[1] + 1100 };


        //Demo
        Hitboxprint.Name = "Image/RBB";
        Hitboxprint.Location = { Body[0].Location[0], Body[0].Location[1] };
        Hitboxprint.Length =   { Body[0].Length[0] ,Body[0].Length[1] };
        
    }

    void Boss::Bossarray::Moving(float const speed, Vector<2> vector)
    {  }
    void Boss::Bossarray::Rendering(BossState state)
    {
        //Demo
        switch (state)
        {
        case BossState::Boss_Idle1:
        {
            
            Body[0].Name = "Animation/Enemy/Boss/Mainbody/Secondfloor";
            Body[1].Name = "Animation/Enemy/Boss/Mainbody/Body1";
            Body[2].Name = "Animation/Enemy/Boss/Mainbody/Body2";
            MainGun.Name = "Animation/Enemy/Boss/Mainweapon/Idle";
            SubGun.Name = "Animation/Enemy/Boss/Subweapon/SubIdle";

            MainGun.Duration = 2.0f;
            MainGun.Length = Vector<2>(220, 250);
           
            if (Motion == false) MainGun.Location = Body[1].Location + Vector<2>(0, -5) + Vector<2>(0, MainGun.Length[1] / 2);
            SubGun.Location = Body[1].Location + Vector<2>(-110, 22);
           
            Body[0].Render();
            Body[2].Render();
         
            if(MainGun.Playback == 0.2f)MainGun.Playback=0.0f; 
            MainGun.Render();
            Body[1].Render();
            if (SubAttack != true)SubGun.Render();
            break;
        }
        case BossState::Boss_Idle2:
        {
            Body[0].Name = "Animation/Enemy/Boss/Mainbody/DamageSecondfloor";
            Body[1].Name = "Animation/Enemy/Boss/Mainbody/Damagebody1";
            Body[2].Name = "Animation/Enemy/Boss/Mainbody/Damagebody2";
            MainGun.Name = "Animation/Enemy/Boss/Mainweapon/Idle";
            SubGun.Name = "Animation/Enemy/Boss/Subweapon/SubIdle";

            MainGun.Duration = 2.0f;
            MainGun.Length = Vector<2>(220, 250);

            if (Motion == false) MainGun.Location = Body[1].Location + Vector<2>(0, -5) + Vector<2>(0, MainGun.Length[1] / 2);
            SubGun.Location = Body[1].Location + Vector<2>(-110, 22);

            Body[0].Render();
            Body[2].Render();

            if (MainGun.Playback == 0.2f)MainGun.Playback = 0.0f;
            MainGun.Render();
            Body[1].Render();
            if (SubAttack != true)SubGun.Render();
            break;
        }
        case BossState::Boss_Attack_Main:
        {
            Body[0].Render();
            Body[2].Render();
            MainGun.Duration = 1.0f;

            if (Left == true)
            {
                MainGun.Name = "Animation/Enemy/Boss/Mainweapon/Fire1";
                MainEffect.Location = MainGun.Location + Vector<2>(-85, -25);
                MainGun.Length = Vector<2>(240, 300);
                MainGun.Location = Body[1].Location + Vector<2>(+10, 20) + Vector<2>(0, MainGun.Length[1] / 2);
            }
            else
            {
                MainGun.Name = "Animation/Enemy/Boss/Mainweapon/Fire2";
                MainEffect.Location = MainGun.Location + Vector<2>(-35, -20);
                MainGun.Length = Vector<2>(220, 290);
                MainGun.Location = Body[1].Location + Vector<2>(0, 20) + Vector<2>(0, MainGun.Length[1] / 2);
            }


            MainGun.Render();
            Body[1].Render();
            MainEffect.Render();
            MainGun.Length = Vector<2>(220, 250);
            if(SubAttack!=true)SubGun.Render();
            break;
        }
        case BossState::Boss_Attack_Sub:
        {
            SubEffect.Location = SubGun.Location + Vector<2>(-10, 42);
            SubGun.Name= "Animation/Enemy/Boss/Subweapon/Subattack";

            SubGun.Render();
            SubEffect.Render();

            SubGun.Name = "Animation/Enemy/Boss/Subweapon/SubIdle";
            break;
        }
        case BossState::Boss_Death:
        {
            Body[1].Name= "Animation/Enemy/Boss/Mainbody/Destory";
            MainGun.Name = "Animation/Enemy/Boss/Mainweapon/DestoryMainGun";
            Body[0].Playback = 0.2f;
            Body[1].Length = Vector<2>(300, 150);
            
            MainEffect.Location = MainGun.Location + Vector<2>(0, +25);
           

            MainGun.Location = Body[1].Location + Vector<2>(+10, -60) + Vector<2>(0, MainGun.Length[1] / 2);
            MainGun.Length = Vector<2>(260, 250);


            Body[0].Render();
            Body[1].Render();
            MainGun.Render();
            MainEffect.Render();
       

            break;
        }

        case BossState::Boss_Intro:
        {
           
            if (IntroTime == 0.0f)
            {
                Cap[0].Location = Body[2].Location + Vector<2>(-50, 50);
                Cap[1].Location = Body[2].Location + Vector<2>(0, 50);
                Cap[2].Location = Body[1].Location + Vector<2>(50, 100);
                MainGun.Name= "Animation/Enemy/Boss/Mainweapon/DeployCannon";
                SubGun.Name= "Animation/Enemy/Boss/Subweapon/DeploySubweapon";
                SubGun.Location = Body[1].Location + Vector<2>(-110, 22);
                MainGun.Length = Vector<2>(220, 250);
            }
            if (IntroTime >= 0.2f && IntroTime < 0.4f)
            {
                Cap[0].Location +=  Vector<2>(-20,0)*Engine::Time::Get::Delta();
                Cap[2].Location +=  Vector<2>(20, 0)*Engine::Time::Get::Delta();
            }
            if (IntroTime >= 0.3f)
            {
                Cap[0].Location += Vector<2>(-30, -100*(0.5+IntroTime)) * Engine::Time::Get::Delta();
                Cap[2].Location += Vector<2>( 30, -100*(0.5+IntroTime))  * Engine::Time::Get::Delta();
                Cap[1].Location += Vector<2>(0,   -100*(0.5+IntroTime)) * Engine::Time::Get::Delta();
                

                Cap[0].Angle += 15 * Engine::Time::Get::Delta();
                Cap[2].Angle -= 15 * Engine::Time::Get::Delta();
            }

            if (IntroTime <= 1.0f)Cap[1].Render();
            Body[0].Render();


            Body[2].Render();
            if (IntroTime > 1.2f)MainGun.Render();

            Body[1].Render();
            if (IntroTime > 2.6f)SubGun.Render();

            if (IntroTime <= 2.1f)Cap[0].Render();
            if (IntroTime <= 2.1f)Cap[2].Render();

          
            break;
        }
  
        }
        Hitboxprint.Render();
        Hitboxprint.Name = "Image/GBB";
    }



    void Boss::Start()
    {
        Bossbody = new Bossarray;

        Hp =300;

        Actorphysics = Bossbody->Hitbox[0];

        bullet1 = &Bomb;
      
            for (int i = 0; i < 9; i++)
            {
                bullet2[i] = &SubBomb[i];
            }
        
    }

    void Boss::Update()
    {


        if (Intro == false && Battle==true)
        {
            if (Hp > 0)
            {
                if (Bossbody->Search.Collide(PlayerTarget->Actorphysics))
                {
                    float const Mainguncooldown = 5.0f;
                    float const Subcooldown = 1.5f;

                    if(Bossbody->Motion==false)MainGunFire += Engine::Time::Get::Delta();
                    if(Startshot[0].Fly==false || Startshot[8].Fly == false || SubBomb[0].Fly == false|| SubBomb[8].Fly==false)SubGunFire += Engine::Time::Get::Delta();

                    if (MainGunFire > Mainguncooldown)Bossbody->Motion = true, Bossbody->MainGun.Playback = 0.0f, MainGunFire = 0.0f;

                    if (SubGunFire > Subcooldown)
                    {
                       
                        if (SubBomb[0].Fly == true || SubBomb[1].Fly == true || SubBomb[2].Fly == true || SubBomb[3].Fly == true || SubBomb[4].Fly == true
                            || SubBomb[5].Fly == true || SubBomb[6].Fly == true || SubBomb[7].Fly == true || SubBomb[8].Fly == true )Bossbody->SubAttack = false;
                        else Bossbody->SubAttack = true;


                        for (int i = 0; i < 9; i++)
                        {
                            Startshot[i].Start(Bossbody->SubGun.Location + Vector<2>(i % 2 == 0 ? -10 : (i % 3 == 0 ? -20 : 0), 50), 0);

                        }
                        SubGunFire = 0.0f;
                    }

                }
                if (Bossbody->Motion == false)
                {
                    if (Hp > 100)Bossbody->Rendering(Boss_Idle1);
                    else Bossbody->Rendering(Boss_Idle2);
                    Bossbody->Rendering(Boss_Intro);
                }
            }
            else
            {
                Bossbody->Rendering(Boss_Death);
                Bossbody->IntroTime +=Engine::Time::Get::Delta();

                Bossbody->Motion = false;
                Bossbody->SubAttack = false;
              
            }
        }

        if(Battle!=true)Bossbody->Rendering(Boss_Intro), Bossbody->Hitboxprint.Name = "Image/RBB";
       
        if (Bossbody->Body->Location[0]-PlayerTarget->Location()<=500.f && Battle==false)Intro = true;

        if (Intro == true)
        {
            if(Battle == false) Hp = 300;
            Bossbody->IntroTime += Engine::Time::Get::Delta();
            if (Bossbody->IntroTime > 3.0f)Intro = false,Battle=true;

        }



        //Main Attack
        if (Bossbody->Motion == true)
        {
      
            if (MainGunCooldown >= 0.0f && MainGunCooldown <= 1.0f)
            {
                Bossbody->MainGun.Playback = 1.0f;
                if(Hp>100)Bossbody->Rendering(Boss_Idle1);
                else Bossbody->Rendering(Boss_Idle2);
                
                Vector<2> Location = Bossbody->MainGun.Location;
                Bossbody->MainGun.Location += Vector<2>(0, 30) * Engine::Time::Get::Delta();
                if (Bossbody->MainGun.Location[1] > Location[1] + 30.0f) Bossbody->MainGun.Location[1] = Location[1] + 30.0f;
            }

            if (MainGunCooldown >= 1.0f && MainGunCooldown <= 1.5f)
            {
                Bossbody->Left = false;
                Bossbody->Rendering(Boss_Attack_Main);
                if (Bomb.Fly != true)Bomb.Start(Bossbody->MainEffect.Location-Vector<2>(20, 20), -30), Bomb.Fly = true;

            }
            if (MainGunCooldown > 1.5f && MainGunCooldown <= 3.5f)
            {
                if (Hp > 100)Bossbody->Rendering(Boss_Idle1);
                else Bossbody->Rendering(Boss_Idle2);
            }
            if (MainGunCooldown > 2.5f && MainGunCooldown <= 3.0f)
            {
                Bossbody->Left = true;
                Bossbody->Rendering(Boss_Attack_Main) ;
                if(Bomb.Fly!=true)Bomb.Start(Bossbody->MainEffect.Location - Vector<2>(55, 25), -50), Bomb.Fly = true;

            }
            if (MainGunCooldown > 3.0f && MainGunCooldown < 3.5f)
            {
                Bossbody->MainGun.Playback = 0.4f;

                if (Hp > 100)Bossbody->Rendering(Boss_Idle1);
                else Bossbody->Rendering(Boss_Idle2);

                Vector<2> Location = Bossbody->MainGun.Location;
                Bossbody->MainGun.Location -= Vector<2>(0, 60) * Engine::Time::Get::Delta();
                if (Bossbody->MainGun.Location[1] > Location[1] + 30.0f) Bossbody->MainGun.Location[1] = Location[1] - 30.0f;
            }
            if(MainGunCooldown>3.5f)MainGunCooldown = 0.0f,   Bossbody->Motion = false;

            MainGunCooldown += Engine::Time::Get::Delta();  
        }

        //Sub Attack
        if (Bossbody->SubAttack == true)
        {
           
         

            Bossbody->Rendering(Boss_Attack_Sub);
            Startshot[SubCount].Update();
            Startshot[SubCount].Fly = true;

            SubTime += Engine::Time::Get::Delta();
            if (SubTime > 0.1f)SubCount++, SubTime =0.0f;
            if (SubCount > 8)SubCount = 0,Bossbody->SubAttack=false;
           
            if (Startshot[8].Fly == false)
            {
                for (int i = 0; i < 9; i++)
                {

                    if(i<4)SubBomb[i].Start(Vector<2>(PlayerTarget->Location()+  i * 70, Bossbody->SubGun.Location[1] + 500 + i * 20), 0.0f)  ,SubBomb[i].Fly=true;
                    else   SubBomb[i].Start(Vector<2>(PlayerTarget->Location()-  (i-3) * 70, Bossbody->SubGun.Location[1] + 500 - (i - 3) * 20), 0.0f),SubBomb[i].Fly=true;
                }
            }

        }
        


        if (Bomb.Fly == true)
        {
            Bomb.Update();
        }
        for (int i = 0; i < 9; i++)
        {
            if (Startshot[i].Fly == true)
            {
                Startshot[i].Update();
           
            }
            if (SubBomb[i].Fly == true)
            {
                SubBomb[i].Update();
            }


        }
        Actorphysics = Bossbody->Hitbox[0];
    }

    void Boss::End()
    {
        Battle = false;
    }

    float Boss::Location()
    {
        return 0.0f;
    }

    void Boss::SelectLocation(Vector<2> location)
    {
        Bossbody->Body[0].Location = { location[0], Bossbody->Body[0].Location[1] };
        Bossbody->Hitbox[0].Center = { Bossbody->Body[0].Location[0], Bossbody->Body[0].Location[1] };
        Bossbody->Search.Center = { Bossbody->Body[0].Location[0], Bossbody->Body[0].Location[1] };

        
        Bossbody->MainGun.Location[0]=Bossbody->Body[2].Location[0] =Bossbody->SubGun.Location[0]= 
        Bossbody->Body[1].Location[0] = Bossbody->Body[0].Location[0];

        Bossbody->Hitboxprint.Location = { Bossbody->Body[0].Location[0],Bossbody->Body[0].Location[1] };
    }

 
 

}