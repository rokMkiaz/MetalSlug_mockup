
#include "Stage1.h"

#include "Game.h"


void Game::Start()
{	
	Now = new Stage1;
	
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
}

void Game::End()
{
	Now->End();
	delete Now;
}