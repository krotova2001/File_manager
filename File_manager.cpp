#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

int main(int argс, char* argv[]) // включим аргументы командной строки для принятия пути каталога, из которого начнет работать программа
{
	fs::path p;
	if (argс > 1) // если передан аргумент - присваиваем его родительскому пути
	{
		p = fs::path(*argv);
	}
	
	cout << "n" << p.root_directory();
}