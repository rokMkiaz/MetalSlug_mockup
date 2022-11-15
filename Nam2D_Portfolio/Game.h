#include "Engine/Game.h"
#include "Engine/Rendering.h"



class Game final : public Engine::Game  //���߿� �����̸� �ٲٸ��
{
public:
    ~Game();

     void  Start() final override;
     void Update() final override;
     void    End() final override;

private:
    class Stage* Now = nullptr; 

 

};