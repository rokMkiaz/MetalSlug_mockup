#include<Windows.h>

namespace Engine
{
    LRESULT CALLBACK Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
}

int APIENTRY WinMain
(
    _In_     HINSTANCE const hInstance,
    _In_opt_ HINSTANCE const hPrevInstance,
    _In_     LPSTR     const lpCmdLine, 
    _In_     int       const nShowCmd 
)

{
    HWND hWindow = nullptr;
    {
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize          = sizeof(WNDCLASSEX); 
        Class.style           = 0      ;           
        Class.lpfnWndProc     = Engine::Procedure;  
        Class.cbClsExtra      = 0;
        Class.cbWndExtra      = 0;
        Class.hInstance       = hInstance;  
        Class.hIcon           = LoadIcon(nullptr/*기본은 null포인터*/,IDI_APPLICATION);
        Class.hCursor         = LoadCursor(nullptr,IDC_ARROW);
        Class.hbrBackground   = static_cast<HBRUSH>/*형변환*/(GetStockObject(BLACK_BRUSH));
        Class.lpszMenuName    = nullptr;
        Class.lpszClassName   = "Window";          
        Class.hIconSm         = LoadIcon(nullptr, IDI_APPLICATION); 

        RegisterClassEx(&Class);
    }
    {
        CREATESTRUCT Window = CREATESTRUCT();    //윈도우 생성자 호출을 위한 함수

     
        Window.dwExStyle                =  0 ;                    
        Window.lpszClass                = "Window" ;               
        Window.lpszName                 = "MetalSlug_NamPortfolio"  ;              
        Window.style                    = WS_SYSMENU | WS_CAPTION; 
        Window.x                        = 0      ;  
        Window.y                        = 0      ;   
        Window.cx                       = 1280   ;   
        Window.cy                       = 720    ;   
        Window.hwndParent               = nullptr ;  
        Window.hMenu                    = nullptr ;  
        Window.hInstance                = hInstance; 
        Window.lpCreateParams           = nullptr;   

        {
            RECT Rect = RECT(); 
            Rect.left = 0;
            Rect.top = 0;
            Rect.right = Window.cx;
            Rect.bottom = Window.cy;
              
            AdjustWindowRectEx(&Rect, Window.style, false, Window.dwExStyle); 
            Window.cx = Rect.right - Rect.left;
            Window.cy = Rect.bottom - Rect.top;

            Window.x = (GetSystemMetrics(SM_CXSCREEN) - Window.cx) / 2;  
            Window.y = (GetSystemMetrics(SM_CYSCREEN) - Window.cy) / 2;   
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
         );  
        ShowWindow(hWindow, SW_RESTORE); 


    }


    {
        
        MSG Message = MSG(); 
       
        
        while (true)
        {
           
            if (PeekMessage(&Message, nullptr, WM_NULL, WM_NULL,PM_REMOVE))
            {
                if (Message.message == WM_QUIT)
                    return static_cast<int>(Message.wParam);

                DispatchMessage(&Message); 
            }
            else
            {
              //PostMessage(hWindow, WM_APP, 0, 0); 
                SendMessage(hWindow, WM_APP, 0, 0);
            }
        }
      

        return static_cast<int>(Message.wParam);

    }
}
