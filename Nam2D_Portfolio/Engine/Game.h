#pragma once
namespace Engine
{
	class Game abstract // interface
	{
	public:
		virtual void Start()   abstract;
		virtual void Update()  abstract;
		virtual void End()     abstract;
	};
}