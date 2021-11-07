#include<Windows.h>
#include "Time.h"
#include<chrono>


namespace Engine::Time
{
	namespace
	{
		std::chrono::steady_clock::time_point const Started = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point       Updated = std::chrono::steady_clock::now();
	

		float Elapsed; 
		float Delta;
	}

	namespace Get
	{
		float Elapsed() { return Time::Elapsed; }
		float   Delta() { return Time::Delta; }

	}

	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParmeter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
		case WM_APP:
		    {
		    	std::chrono::steady_clock::time_point const now = std::chrono::steady_clock::now();
		    	
		    	Elapsed=std::chrono::duration_cast<std::chrono::duration<float>>(now - Started).count();
		    	Delta  =std::chrono::duration_cast<std::chrono::duration<float>>(now - Updated).count();
		    	
		    	Updated = now;
		    
		    
		    	return;
		    }
		}
	}
}

