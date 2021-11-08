#include "Engine/Initialize.h"


#include "Game.h"

namespace Engine
{
    Game * Initialize()
    {
        return new ::Game;
    }
}