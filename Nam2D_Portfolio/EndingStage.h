#pragma once
#include "Stage.h"

#include "Engine\Rendering.h"
#include"Actor.h"

namespace Lose
{
	class LoseStage : public Stage
	{


		virtual void Start()    final override;
		virtual Stage* Update() final override;
		virtual void End()      final override;

		Engine::Rendering::Image::Component		LoseStage;
		Engine::Rendering::Camera				camera;
		Engine::Rendering::Text::Component		Text;

		float delay = 0.0f;



	};
}
namespace Clear
{
	class ClearStage : public Stage
	{
	

		virtual void Start()     override;
		virtual Stage* Update()  override;
		virtual void End()       override;

		class Actor* Player;

		Engine::Rendering::Image::Component		ClearStage;
		Engine::Rendering::Camera				camera;
		Engine::Rendering::Text::Component		Text;


		float delay = 0.0f;

	};


}
