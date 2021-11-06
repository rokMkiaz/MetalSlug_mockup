#include <filesystem> //파일을 다루는 cpp표준 헤더

#include "Resource.h"

namespace Engine::Resource
{
	void Import(std::string const directory, void(* const function)(std::string const& file))
	{
		if (std::filesystem::exists(directory)) //directory(폴더)가 존재하는지 확인하는 구문
		{
			for (std::filesystem::path const& path : std::filesystem::recursive_directory_iterator(directory)/*지정한 디렉토리로부터 모든 폴더와 파일을 검색함*/)//원소하나별로 반복
			{
				if (std::filesystem::is_regular_file(path))//파일인지 아닌지 확인
				{
					std::string file = path.string(); //경로를 받아옴

					std::replace(file.begin(), file.end(), '\\', '/'); //  '\\'문자를 전부 /로 바꾼다.

					function(file);
				}
			}
		}
		else
		{
			std::filesystem::create_directories(directory);//폴더가 없을경우 만든다.
		}
	}
}