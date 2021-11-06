#pragma once

namespace Engine:: Physics  //�浹�� �˻��ϴ� ����
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

