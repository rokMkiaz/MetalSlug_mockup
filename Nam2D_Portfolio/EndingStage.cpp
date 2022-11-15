#include "EndingStage.h"
#include"Engine\Time.h"
#include "Engine\Input.h"
#include "Slug.h"

#include"Mainmenu.h"

namespace Lose
{

    void LoseStage::Start()
    {
        
        LoseStage.Name = "Image/Gameover";
        LoseStage.Length = Vector<2>(1280, 720);

        camera.Sight = Vector<2>(1280, 720);
        camera.Location = Vector<2>(0, 0);

        Text.Font.Name = "돋음";
        Text.Font.Bold = true;

        Text.Length = Vector<2>(600, 500);
        Text.Font.Size = 25;
        Text.Location = Vector<2>(1250, 900);
        Text.Color = { 255,255,255 };

        Text.Text = "'K'키를 누르면 매뉴로 돌아갑니다.";

    }

    Stage* LoseStage::Update()
    {
        delay += Engine::Time::Get::Delta();
        LoseStage.Render();
        camera.Set();

        if (delay > 1.0f)
        {
            Text.Render();
            if (Engine::Input::Get::Key::Down('K'))
            {
                return new Mainmenu;
            }

        }
        return nullptr;
    }

    void LoseStage::End()
    {

    }
}

namespace Clear
{
    void ClearStage::Start()
    {
   

        ClearStage.Name = "Image/EndingSheet";
        ClearStage.Length = Vector<2>(400, 1000);
        ClearStage.Location = Vector<2>(0, -ClearStage.Length[1] );

        camera.Sight = Vector<2>(1280, 720);
        camera.Location = Vector<2>(0, 0);

        Text.Font.Name = "돋음";
        Text.Font.Bold = true;

        Text.Length = Vector<2>(600, 500);
        Text.Font.Size = 25;
        Text.Location = Vector<2>(1250, 900);
        Text.Color = { 255,255,255 };

        Text.Text = "'K'키를 누르면 매뉴로 돌아갑니다.";


    }
    Stage* ClearStage::Update()
    {
        camera.Set();
        ClearStage.Render();
        camera.Location -= Vector<2>(0, 100) * Engine::Time::Get::Delta();
        Text.Render();
        delay += Engine::Time::Get::Delta();

        if (Engine::Input::Get::Key::Down('K') || delay > 25.0f) return new Mainmenu;


   

        return nullptr;
    }
    void ClearStage::End()
    {
    }
}