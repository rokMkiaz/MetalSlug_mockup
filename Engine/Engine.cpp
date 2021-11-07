#include <Windows.h>


#include"Point.h"
#include"Quadrangle.h"
#include"Circle.h"

#include"Input.h"
#include"Time.h"
#include"Physics.h"
#include"Rendering.h"

#include"Game.h"
#include"Initialize.h"


namespace Engine
{
    namespace Input { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }
    namespace Time  { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }
    namespace Rendering { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }

    namespace 
    {
        Game*  Portfolio = Initialize();
    
    }

    LRESULT CALLBACK Procedure
    (   HWND const hWindow,
        UINT const uMessage,
        WPARAM const wParameter,
        LPARAM const lParameter 
        /*W,L PARAM메세지별 세부 정보 정확한 내용은 내부적으로 나뉘어져있음*/
    )

    {
        //윈도우 프로시저 특정 윈도우 클래스의 인스턴스로부터 발생한 메세지를 처리하는 함수.


        switch (uMessage)
        {

        case WM_CREATE:    //생성직후 생성자와 같음, lParmeter로 CRATESTRUCT Window의 인자값이 포인터로 입력
        {
   
            //과제: 윈도우즈좌표계의 한점을 월드좌표계로 변환하려면 어떤변환이 필요한가?



            Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

          

            Portfolio->Start();


            return 0;
        }


        case WM_APP:
        {
            Portfolio->Update();


            Input::Procedure(hWindow, uMessage, wParameter, lParameter);
             Time::Procedure(hWindow, uMessage, wParameter, lParameter);

            Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);


            return 0;
        }
        case WM_DESTROY: //창이 파괴 될때  소멸자와 동일
        {

            Portfolio->End();
            delete Portfolio;
  
            Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);

            PostQuitMessage(0); //프로그램 완전 종료를 위해 필요.

            return 0;
        }

        
        case WM_MOUSEWHEEL:  case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
        case WM_SYSKEYDOWN:  case WM_LBUTTONDOWN: case WM_LBUTTONUP:
        case WM_SYSKEYUP:    case WM_RBUTTONDOWN: case WM_RBUTTONUP:
        case WM_KEYDOWN:     case WM_MBUTTONDOWN: case WM_MBUTTONUP:
        case WM_KEYUP:       case WM_XBUTTONDOWN: case WM_XBUTTONUP:
        {
            Input::Procedure(hWindow, uMessage, wParameter, lParameter);
            

            return 0;
        }
        case WM_SIZE:
        {
            Rendering::Procedure(hWindow, uMessage, wParameter, lParameter);
            return 0;
        }
        default: //기본 상태
        {
            return DefWindowProc(hWindow, uMessage, wParameter, lParameter);    // Close동작을 할 경우 자동으로 Destroy명령을 내린다.
        }
        break;
        }


        return 0;
    }
}