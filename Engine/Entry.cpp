#include<Windows.h>

namespace Engine
{
    LRESULT CALLBACK Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
}
/*
  cdecl:일반함수에 기본적으로 적용
  stdcall:Windows API함수
  this call:맴버함수
*/

int APIENTRY WinMain
(
    _In_     HINSTANCE const hInstance,//해당 윈도우가 어느 프로그램에 속하는지 알려주는 ID값
    _In_opt_ HINSTANCE const hPrevInstance,
    _In_     LPSTR     const lpCmdLine, // 명령어 기입
    _In_     int       const nShowCmd //윈도우 최소화,최대화
)
// WinBase.h파일에서 ctrl f로 WinMain만 추가
/*
  _In_ : 유의미한 포인터여야 한다.
  _In_opt_ : 무관
*/


/*
  Register -> Create ->Show -> Run ->(Close -> Destory -> Unregister) 
*/
{
    HWND hWindow = nullptr;
    {
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize          = sizeof(WNDCLASSEX); //count byte 바이트단위 수;
        Class.style           = 0      ;            //CS_HREDRAW | CS_VREDRAW; 스타일 비트마스킹
        Class.lpfnWndProc     = Engine::Procedure;  //윈도우 메세지 처리 구역 call back방식
        Class.cbClsExtra      = 0;
        Class.cbWndExtra      = 0;
        Class.hInstance       = hInstance;  
        Class.hIcon           = LoadIcon(nullptr/*기본은 null포인터*/,IDI_APPLICATION);
        Class.hCursor         = LoadCursor(nullptr,IDC_ARROW);
        Class.hbrBackground   = static_cast<HBRUSH>/*형변환*/(GetStockObject(BLACK_BRUSH))/*void pointer ->HBRUSH로 변환*/;//윈도우 백그라운드색
        Class.lpszMenuName    = nullptr;
        Class.lpszClassName   = "Window";          //class 이름   
        Class.hIconSm         = LoadIcon(nullptr/*기본은 null포인터*/, IDI_APPLICATION); //창옆에 띄우는 작은 아이콘

        RegisterClassEx(&Class);//윈도우에 등록 
    }
    {
        CREATESTRUCT Window = CREATESTRUCT();    //윈도우 생성자 호출을 위한 함수

     
        Window.dwExStyle                =  0 ;                     //창호출을 어느순으로 하는지
        Window.lpszClass                = "Window" ;               //어떤 클래스이름을 따를지 지정
        Window.lpszName                 = "Game"  ;                // 객체 이름
        Window.style                    = WS_SYSMENU | WS_CAPTION; 
        /*
          WS_OVERLAPPEDWINDOW =; //통상적인 윈도우창(비트마스킹 구조로 되어있음)
          WS_OVERLAPPED   : 윈도우 겹침
          WS_CAPTION      : 제목표시줄이 있나 없나/그러나 시스템창 크기계산시 맞출려면 필수로 입력해야함.
          WS_SYSMENU      : x버튼 유무
          WS_THICKFRAME   : 시스템창 줄이기 키우기
          WS_MINIMIZEBOX  : 최소화, 최대화 버튼
          WS_MAXIMIZEBOX)
        */
        Window.x                        = 0      ;   //CreateWindow
        Window.y                        = 0      ;   
        Window.cx                       = 1280   ;   //사이즈
        Window.cy                       = 720    ;   
        Window.hwndParent               = nullptr ;  //부모 윈도우, 최상위 윈도우에게는 필요 없음. EX)설정창
        Window.hMenu                    = nullptr ;  //메뉴
        Window.hInstance                = hInstance; 
        Window.lpCreateParams           = nullptr;   // 설명은 나중에

        {
            RECT Rect = RECT(); //작업영역에 제한되지 않게 만들기 위해 선언
            Rect.left = 0;
            Rect.top = 0;
            Rect.right = Window.cx;
            Rect.bottom = Window.cy;
              
            AdjustWindowRectEx(&Rect, Window.style, false/*창 내부 메뉴가 있는지*/, Window.dwExStyle); //작업영역을 알려주기 위한 수정값계산을 위해 &Rect를 보내주어 조정하는 것
            Window.cx = Rect.right - Rect.left;
            Window.cy = Rect.bottom - Rect.top;

            Window.x = (GetSystemMetrics(SM_CXSCREEN) - Window.cx) / 2;   //(화면 해상도(W)-원하는 화면 가로축)/2
            Window.y = (GetSystemMetrics(SM_CYSCREEN) - Window.cy) / 2;   //(화면 해상도(H)-원하는 화면 세로축)/2
        }



        hWindow=CreateWindowEx  
        (
            Window.dwExStyle,
            Window.lpszClass,
            Window.lpszName,
            Window.style,
            Window.x,
            Window.y,
            Window.cx,
            Window.cy,
            Window.hwndParent,
            Window.hMenu,
            Window.hInstance,
            Window.lpCreateParams
         );  //Create 메세지 발송시점
        ShowWindow(hWindow, SW_RESTORE); //Cmd Show값 플래그


    }


    {
        //운영체제로부터 메세지를 받는 위치, Message loof 지역

        MSG Message = MSG(); // 생성되는 모든 멤버를 0으로 초기화
        //W,L PARAM 
        //WM_QUIT;

        while (true)//메세지 포인터, 어느 윈도우 정보 받을것인지, message를 몇번부터 몇번까지 받을지 설정//메세지를 성공적으로 받으면 1,메세지가 없으면 무한 대기
        {
            //Peek   Remove면 GetMessage와 같은 함수
            if (PeekMessage(&Message, nullptr, WM_NULL, WM_NULL,PM_REMOVE))
            {
                if (Message.message == WM_QUIT)
                    return static_cast<int>(Message.wParam);//64비트구성에서는  static_cast<int>해줘야함

                DispatchMessage(&Message); //메세지큐에서 해당하는 wndProc로 메세지를 보내줌
            }
            else //메세지큐가 비었을 때 다이렉트로 보내게 해주기위해 SendMessage를 사용한다. 윈도우 메세지 처리할게 없을 때 업데이트를 목적으로 만듬
            {
              //PostMessage(hWindow, WM_APP, 0, 0); //메세지큐에 보낸 이후 메세지를 보낸다
                SendMessage(hWindow, WM_APP, 0, 0); //바로 Proc 메세지를 보낸다 WM_APP:사용자 정의 메세지(0x8000,0xbfff 까지)
            }
        }
        //어느 클래스에서 만들어졌는지, 어디에 존재하는지 알게됨.


        return static_cast<int>(Message.wParam);

    }
}