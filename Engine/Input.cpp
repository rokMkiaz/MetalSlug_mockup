#include <Windows.h>

#include "Input.h"



namespace Engine::Input
{

	namespace
	{
		class    // bit Matrix
		{
		public:
			void Update()
			{
				ZeroMemory(State.Changed, sizeof(State.Changed));
			} 


			void Down(WORD const code)
			{
				if (not Pressed(code))
				{
				State.Changed[code >> 0x4 /*/16*/] ^= (0x8000 >> (code & 0xF));
				State.Pressed[code >> 0x4 /*/16*/] ^= (0x8000 >> (code & 0xF));
				}
			}
			void Up(WORD const code)
			{
				State.Changed[code >> 0x4 ] ^= (0x8000 >> (code & 0xF));
				State.Pressed[code >> 0x4 ] ^= (0x8000 >> (code & 0xF));
				
			}

			bool Changed(WORD const code)
			{

				return State.Changed[code >> 0x4 /*/16*/] & (0x8000 >> (code & 0xF));
			}
			bool Pressed(WORD const code)
			{

				return State.Pressed[code>>0x4 /*/16*/]&(0x8000>>(code&0xF));
			}

		private:
			struct
			{
				WORD Changed[16];
				WORD Pressed[16];
			}State;

		}Key;
		POINT Cursor;
		POINT Wheel;
	}

	namespace Get
	{
		namespace Key
		{
			 bool Press (WORD const code)  { return     Input::Key.Pressed(code)                             ; }
			 bool Down  (WORD const code)  { return     Input::Key.Pressed(code) and Input::Key.Changed(code); }
			 bool Up    (WORD const code)  { return not Input::Key.Pressed(code) and Input::Key.Changed(code); }
		}
		namespace Cursor
		{
			 long X() {return Input::Cursor.x;}
			 long Y() {return Input::Cursor.y;}
		}
		namespace Wheel
		{
			long H() { return Input::Wheel.x; }
			long V() { return Input::Wheel.y; }
		}
	}




	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParmeter, LPARAM const lParameter)
	{
		switch (uMessage)
		{

		case WM_APP:
		{
			Key.Update();

			Wheel = POINT();
			return;
		}
		case WM_MOUSEWHEEL:  { Wheel.x += static_cast<short> (wParmeter >>16&0xFFFF)/WHEEL_DELTA ; return; } 
		case WM_MOUSEHWHEEL: { Wheel.y += GET_WHEEL_DELTA_WPARAM(wParmeter) / WHEEL_DELTA;         return; }
		case WM_MOUSEMOVE:
		{

			Cursor.x = static_cast<SHORT>(LOWORD(lParameter));
			Cursor.y = static_cast<SHORT>(HIWORD(lParameter));
			return;
		}

		case WM_LBUTTONDOWN:  {Key.Down(VK_LBUTTON); return; }
		case WM_LBUTTONUP:    {Key.Up  (VK_LBUTTON); return; }

		case WM_RBUTTONDOWN:  {Key.Down(VK_RBUTTON); return; }
		case WM_RBUTTONUP:    {Key.Up  (VK_RBUTTON); return; }
	
		case WM_MBUTTONDOWN:  {Key.Down(VK_MBUTTON); return; }
		case WM_MBUTTONUP:    {Key.Up  (VK_MBUTTON); return; }
	
		case WM_XBUTTONDOWN: 
		{
			switch (GET_XBUTTON_WPARAM(wParmeter))
			{
			case XBUTTON1: Key.Down(VK_XBUTTON1); return;
			case XBUTTON2: Key.Down(VK_XBUTTON2); return;
			}
		
		}
		case WM_XBUTTONUP:
		{
			switch (GET_XBUTTON_WPARAM(wParmeter))
			{
			case XBUTTON1: Key.Up(VK_XBUTTON1); return;
			case XBUTTON2: Key.Up(VK_XBUTTON2); return;
			}

		}
		
		case WM_SYSKEYDOWN:  case WM_KEYDOWN:  {Key.Down (static_cast<WORD>(wParmeter)); return; }
		case WM_SYSKEYUP:    case WM_KEYUP:    {Key.Up   (static_cast<WORD>(wParmeter)); return; }
		



		}


	}

}
