#pragma once

#include<string>

namespace Engine::Resource
{

	void Import(std::string const directory, void (* const function)(std::string const& file));
	
}
