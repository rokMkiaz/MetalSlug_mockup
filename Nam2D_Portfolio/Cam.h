#pragma once

class Cam
{
public:
	virtual   void    Start() abstract;
	virtual   void   Update() abstract;
	virtual   void	    End() abstract;
	
	Engine::Rendering::Camera cam;
};