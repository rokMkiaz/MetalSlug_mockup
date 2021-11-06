#pragma once

namespace Engine:: Physics  //충돌을 검사하는 내용
{
	template<typename Shape>
	class Component final : public Shape
	{
	public:
		Component();
		Component(Shape const&);

		template<typename Shape>
		[[nodiscard]] bool Collide(Component<Shape>const&) const;

	};


}

