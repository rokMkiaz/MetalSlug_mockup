#include"Engine\Input.h"
#include"Engine\Time.h"

#include "Mainmenu.h"
#include "Stage1.h"


void Mainmenu::Start()
{
    Log.Name = "Image/MetalSluglog";
    Log.Length= Vector<2>(600, 300);
    Log.Location = Vector<2>(-300, 200);

    ManuStage.Name = "Image/Mainmanu";
    ManuStage.Length = Vector<2>(1300, 800);

    KeyImage.Name = "Image/Key";
    KeyImage.Length = Vector<2>(300, 300);
    KeyImage.Location = Vector<2>(-400, -200);

    camera.Sight = Vector<2>(1280, 720);
    camera.Location = Vector<2>(0, 0);

    Text.Font.Name = "돋음";
    Text.Font.Bold = true;
    Text.Length = Vector<2>(600, 500);
    Text.Font.Size = 30;
    Text.Location = Vector<2>(1100, 850);
    Text.Color = { 255,255,255 };
    Text.Text = "W,S로 선택하여 'K'키 눌러 선택해 주십시요.";

    StartText.Font.Name = "Sitka Small";
    StartText.Font.Bold = true;

    StartText.Length = Vector<2>(700, 500);
    StartText.Location = Vector<2>(1400, 600);
    StartText.Text = "Start";
    StartText.Font.Size = 80;
    StartText.Color = { 255,255,0 };

    EndText.Font.Name = "Sitka Small";
    EndText.Length = Vector<2>(700, 500);
    EndText.Text = "End";
    EndText.Font.Size = 70;
    EndText.Location = Vector<2>(1400, 700);
    EndText.Font.Bold = false;
    EndText.Color = { 255,255,255 };

}

Stage* Mainmenu::Update()
{
    delay += Engine::Time::Get::Delta();
    ManuStage.Render();
    KeyImage.Render();
    Log.Render();

   
    camera.Set();

    StartText.Render();
    EndText.Render();
  
    Text.Render();
    if (Engine::Input::Get::Key::Down('W'))
    {
        StartText.Font.Size = 80;
        StartText.Location = Vector<2>(1400, 600);
        StartText.Font.Bold = true;
        StartText.Color = { 255,255,0 };
      
        EndText.Font.Size = 70;
        EndText.Location = Vector<2>(1400, 700);
        EndText.Font.Bold = false;
        EndText.Color = { 255,255,255 };

        Select = true;

    }
    if (Engine::Input::Get::Key::Down('S'))
    {
        StartText.Font.Size = 70;
        StartText.Location = Vector<2>(1400, 600);
        StartText.Font.Bold = false;
        StartText.Color = { 255,255,255 };

        EndText.Font.Size = 80;
        EndText.Location = Vector<2>(1400, 700);
        EndText.Font.Bold = true;
        EndText.Color = { 255,255,0 };

        Select = false;
    }

    
    if (delay == 4)delay = 4;

    switch (Select)
    {
    case true:
      

        if (Engine::Input::Get::Key::Down('K'))  return new Stage1;

        break;

    case false:


        if (Engine::Input::Get::Key::Down('K'))  end = true;

        break;
    }



    return nullptr;



    return nullptr;
}

void Mainmenu::End()
{
}
