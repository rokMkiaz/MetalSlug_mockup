#include "Engine/Game.h"
#include "Engine/Rendering.h"



class Game final : public Engine::Game  //나중에 게임이름 바꾸면됨
{
public:
     void  Start() final override;
     void Update() final override;
     void    End() final override;

private:
    class Stage* Now = nullptr; 

 

};