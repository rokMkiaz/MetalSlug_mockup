#include<Windows.h>

namespace Engine
{
    LRESULT CALLBACK Procedure(HWND const, UINT const, WPARAM const, LPARAM const);
}
/*
  cdecl:�Ϲ��Լ��� �⺻������ ����
  stdcall:Windows API�Լ�
  this call:�ɹ��Լ�
*/

int APIENTRY WinMain
(
    _In_     HINSTANCE const hInstance,//�ش� �����찡 ��� ���α׷��� ���ϴ��� �˷��ִ� ID��
    _In_opt_ HINSTANCE const hPrevInstance,
    _In_     LPSTR     const lpCmdLine, // ��ɾ� ����
    _In_     int       const nShowCmd //������ �ּ�ȭ,�ִ�ȭ
)
// WinBase.h���Ͽ��� ctrl f�� WinMain�� �߰�
/*
  _In_ : ���ǹ��� �����Ϳ��� �Ѵ�.
  _In_opt_ : ����
*/


/*
  Register -> Create ->Show -> Run ->(Close -> Destory -> Unregister) 
*/
{
    HWND hWindow = nullptr;
    {
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize          = sizeof(WNDCLASSEX); //count byte ����Ʈ���� ��;
        Class.style           = 0      ;            //CS_HREDRAW | CS_VREDRAW; ��Ÿ�� ��Ʈ����ŷ
        Class.lpfnWndProc     = Engine::Procedure;  //������ �޼��� ó�� ���� call back���
        Class.cbClsExtra      = 0;
        Class.cbWndExtra      = 0;
        Class.hInstance       = hInstance;  
        Class.hIcon           = LoadIcon(nullptr/*�⺻�� null������*/,IDI_APPLICATION);
        Class.hCursor         = LoadCursor(nullptr,IDC_ARROW);
        Class.hbrBackground   = static_cast<HBRUSH>/*����ȯ*/(GetStockObject(BLACK_BRUSH))/*void pointer ->HBRUSH�� ��ȯ*/;//������ ��׶����
        Class.lpszMenuName    = nullptr;
        Class.lpszClassName   = "Window";          //class �̸�   
        Class.hIconSm         = LoadIcon(nullptr/*�⺻�� null������*/, IDI_APPLICATION); //â���� ���� ���� ������

        RegisterClassEx(&Class);//�����쿡 ��� 
    }
    {
        CREATESTRUCT Window = CREATESTRUCT();    //������ ������ ȣ���� ���� �Լ�

     
        Window.dwExStyle                =  0 ;                     //âȣ���� ��������� �ϴ���
        Window.lpszClass                = "Window" ;               //� Ŭ�����̸��� ������ ����
        Window.lpszName                 = "Game"  ;                // ��ü �̸�
        Window.style                    = WS_SYSMENU | WS_CAPTION; 
        /*
          WS_OVERLAPPEDWINDOW =; //������� ������â(��Ʈ����ŷ ������ �Ǿ�����)
          WS_OVERLAPPED   : ������ ��ħ
          WS_CAPTION      : ����ǥ������ �ֳ� ����/�׷��� �ý���â ũ����� ������� �ʼ��� �Է��ؾ���.
          WS_SYSMENU      : x��ư ����
          WS_THICKFRAME   : �ý���â ���̱� Ű���
          WS_MINIMIZEBOX  : �ּ�ȭ, �ִ�ȭ ��ư
          WS_MAXIMIZEBOX)
        */
        Window.x                        = 0      ;   //CreateWindow
        Window.y                        = 0      ;   
        Window.cx                       = 1280   ;   //������
        Window.cy                       = 720    ;   
        Window.hwndParent               = nullptr ;  //�θ� ������, �ֻ��� �����쿡�Դ� �ʿ� ����. EX)����â
        Window.hMenu                    = nullptr ;  //�޴�
        Window.hInstance                = hInstance; 
        Window.lpCreateParams           = nullptr;   // ������ ���߿�

        {
            RECT Rect = RECT(); //�۾������� ���ѵ��� �ʰ� ����� ���� ����
            Rect.left = 0;
            Rect.top = 0;
            Rect.right = Window.cx;
            Rect.bottom = Window.cy;
              
            AdjustWindowRectEx(&Rect, Window.style, false/*â ���� �޴��� �ִ���*/, Window.dwExStyle); //�۾������� �˷��ֱ� ���� ����������� ���� &Rect�� �����־� �����ϴ� ��
            Window.cx = Rect.right - Rect.left;
            Window.cy = Rect.bottom - Rect.top;

            Window.x = (GetSystemMetrics(SM_CXSCREEN) - Window.cx) / 2;   //(ȭ�� �ػ�(W)-���ϴ� ȭ�� ������)/2
            Window.y = (GetSystemMetrics(SM_CYSCREEN) - Window.cy) / 2;   //(ȭ�� �ػ�(H)-���ϴ� ȭ�� ������)/2
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
         );  //Create �޼��� �߼۽���
        ShowWindow(hWindow, SW_RESTORE); //Cmd Show�� �÷���


    }


    {
        //�ü���κ��� �޼����� �޴� ��ġ, Message loof ����

        MSG Message = MSG(); // �����Ǵ� ��� ����� 0���� �ʱ�ȭ
        //W,L PARAM 
        //WM_QUIT;

        while (true)//�޼��� ������, ��� ������ ���� ����������, message�� ������� ������� ������ ����//�޼����� ���������� ������ 1,�޼����� ������ ���� ���
        {
            //Peek   Remove�� GetMessage�� ���� �Լ�
            if (PeekMessage(&Message, nullptr, WM_NULL, WM_NULL,PM_REMOVE))
            {
                if (Message.message == WM_QUIT)
                    return static_cast<int>(Message.wParam);//64��Ʈ����������  static_cast<int>�������

                DispatchMessage(&Message); //�޼���ť���� �ش��ϴ� wndProc�� �޼����� ������
            }
            else //�޼���ť�� ����� �� ���̷�Ʈ�� ������ ���ֱ����� SendMessage�� ����Ѵ�. ������ �޼��� ó���Ұ� ���� �� ������Ʈ�� �������� ����
            {
              //PostMessage(hWindow, WM_APP, 0, 0); //�޼���ť�� ���� ���� �޼����� ������
                SendMessage(hWindow, WM_APP, 0, 0); //�ٷ� Proc �޼����� ������ WM_APP:����� ���� �޼���(0x8000,0xbfff ����)
            }
        }
        //��� Ŭ�������� �����������, ��� �����ϴ��� �˰Ե�.


        return static_cast<int>(Message.wParam);

    }
}