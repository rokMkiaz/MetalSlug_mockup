#pragma once



namespace Engine::Input

{
	namespace Get
	{
		namespace Key
		{
			[[nodiscard]] bool Down (unsigned short const code);
			[[nodiscard]] bool Press(unsigned short const code);
			[[nodiscard]] bool Up   (unsigned short const code);

			
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

