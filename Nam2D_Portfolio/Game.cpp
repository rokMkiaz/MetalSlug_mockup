
#include "Stage1.h"
#include"Mainmenu.h"

#include"EndingStage.h"



#include "Game.h"


void Game::Start()
{	
    Now = new Mainmenu;
	
	Now->Start();


}

void Game::Update()
{
    Stage* const Next = Now->Update();


    if (Next != nullptr)
    {
        Now->End();

        delete Now;

        Now = Next;

        Now->Start();
    }
    if (Now->end == true)End();

   
}

void Game::End()
{
	Now->End();
	delete Now;
}