//класс жесткого диска

#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <Windows.h>
using namespace std;
namespace fs = std::filesystem;
class HardDisk
{
public:
	struct Hard //описание имени и типа диска
	{
		string name;
		string type;
	};
	vector<Hard> lst;

	HardDisk() // в конструкторе по умолчанию заполняется встроенный список структурами с информацией о дисках
	{
		
		char m[1024];
		char sm[1024];
		char t[1024];
		HANDLE find = FindFirstVolumeA(m, 1024);
		if (find != INVALID_HANDLE_VALUE)
		{
			do
			{
				char sm[1024];
				DWORD ln;
				GetVolumePathNamesForVolumeNameA(m, sm, 1024, &ln);

				Hard hr;

				hr.name = sm;
				std::error_code er;
				if ((hr.name != "") && fs::exists(hr.name, er))
				{
					switch (GetDriveTypeA(m))
					{
					case DRIVE_REMOVABLE:
					{
						hr.type = "REMOVABLE";
						break;
					}
					case DRIVE_FIXED:
					{
						hr.type = "FIXED";
						break;
					}
					case DRIVE_REMOTE:
					{
						hr.type = "REMOTE";
						break;
					}


					}
				}
				lst.push_back(hr);
			} while (FindNextVolumeA(find, m, 1024));
			FindVolumeClose(find);
		}
		
	}
};

