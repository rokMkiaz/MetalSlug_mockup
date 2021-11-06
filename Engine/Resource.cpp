#include <filesystem> //������ �ٷ�� cppǥ�� ���

#include "Resource.h"

namespace Engine::Resource
{
	void Import(std::string const directory, void(* const function)(std::string const& file))
	{
		if (std::filesystem::exists(directory)) //directory(����)�� �����ϴ��� Ȯ���ϴ� ����
		{
			for (std::filesystem::path const& path : std::filesystem::recursive_directory_iterator(directory)/*������ ���丮�κ��� ��� ������ ������ �˻���*/)//�����ϳ����� �ݺ�
			{
				if (std::filesystem::is_regular_file(path))//�������� �ƴ��� Ȯ��
				{
					std::string file = path.string(); //��θ� �޾ƿ�

					std::replace(file.begin(), file.end(), '\\', '/'); //  '\\'���ڸ� ���� /�� �ٲ۴�.

					function(file);
				}
			}
		}
		else
		{
			std::filesystem::create_directories(directory);//������ ������� �����.
		}
	}
}