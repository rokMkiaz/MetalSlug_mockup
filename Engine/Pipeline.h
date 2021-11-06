#pragma once
namespace Engine::Rendering::Pipeline
{
	namespace String
	{
		void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const& size, POINT const& center);

	}


	namespace Texture
	{
	
		void Create(struct Handle*& handle, SIZE const& size, BYTE const* const date);
		void Render(struct Handle const* const& handle, RECT const& area);
		void Delete(struct Handle* const& handle);

		
	}
	namespace Transform
	{
		enum class Type
		{
			World,
			View,
			Projection
		};
		using Matrix = float[4][4]; //typedef

		template<Type type>
		void Update(Matrix const& matrix);
	}
}

