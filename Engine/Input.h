#pragma once



namespace Engine::Input

{
	namespace Get
	{
		namespace Key
		{
			[[nodiscard]] bool Down(WORD const code);
			[[nodiscard]] bool Press(WORD const code);
			[[nodiscard]] bool Up(WORD const code);

			
		}
		namespace Cursor
		{
			[[nodiscard]] long X();
			[[nodiscard]] long Y();
		}
		namespace Wheel
		{
			[[nodiscard]] long H();
			[[nodiscard]] long V();
		}
	}

}

