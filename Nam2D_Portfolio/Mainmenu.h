#pragma once

#include "Stage.h"
#include "Engine\Rendering.h"



class Mainmenu :    public Stage
{
	virtual void Start()	final override;
	virtual Stage* Update() final override;
	virtual void End()		final override;

	Engine::Rendering::Image::Component     Log;
	Engine::Rendering::Image::Component		ManuStage;
	Engine::Rendering::Image::Component     KeyImage;
	Engine::Rendering::Camera				camera;

	Engine::Rendering::Text::Component		Text;
	Engine::Rendering::Text::Component		StartText;
	Engine::Rendering::Text::Component		EndText;

	bool Select  =true;

	float delay = 0.0f;
};

