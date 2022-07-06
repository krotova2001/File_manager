#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <fstream>
#include "HardDisk.h" // испорт объекта, который отображает информацию о жестких дисках

struct Hard //описание имени и типа диска
{
    string name;
    string type;
};

using namespace std;
namespace fs = std::filesystem; // сократим пространство имен

void Create_dir(std::filesystem::path p, string s) // функция создания директории. ПРинимает название директории и путь
{
    if (fs::create_directories(p / s))
        cout << "Папка " << s << " создана успешно\n";
    else
    {
        cout << "Произошла ошибка\n";
    }
}

void Remoove_file(std::filesystem::path p, string s) // функция создания директории. ПРинимает название директории и путь
{
    if (fs::remove(p / s))
        cout << "Файл " << s << " удален успешно\n";
    else
    {
        cout << "Произошла ошибка\n";
    }
}

void Remoove_dir(std::filesystem::path p) // функция удаления директории. Принимает путь
{
    cout << "Удалить текущую директорию?? (0 - отмена)\n";
    int ch;
    cin >> ch;
    if (ch)
    {
        if (fs::remove_all(p))
            cout << "Директория " << p << " удалена\n";
        else
        {
            cout << "Произошла ошибка\n";
        }
    }
}

void Rename(std::filesystem::path p)
{
    string old_name, new_name;
    cout << "Введите имя исходного файла\n";
    cin >> old_name;
    fs::path p1 = p / old_name;
    if (p1.has_filename())
    {
        cout << "Введите имя нового файла\n";
        cin >> new_name;
        fs::path p2 = p / new_name;
        fs::rename(p1, p2);
        if (p1.has_stem())
        {
            cout << "Успешно\n";
        }
        else
        {
            cout << "Ошибка\n";
            return;
        }
    }   
    else
    {
        cout << "Исходный файл не существует\n";
        return;
    }
}

void Moove(std::filesystem::path p)
{
    string old_name, new_path;
    cout << "Введите имя исходного файла\n";
    cin >> old_name;
    fs::path old_path = p / old_name;
  
    cout << "Введите имя нового пути\n";
    cin >> new_path;

    fs::path new_path_full = fs::path{ new_path };
    new_path_full /=  old_name;
    if (old_path.has_filename())
    {
        fs::rename(old_path, new_path_full);
        if (new_path_full.has_stem())
        {
                cout << "Успешно\n";
        }
        else
        {
            cout << "Ошибка\n";
            return;
        }
    }
    else
    {
        cout << "Исходный файл не существует\n";
        return;
    }
}

void Read(std::filesystem::path p)
{
    string name;
    cout << "Введите имя файла\n";
    cin >> name;
    ifstream file;
    file.open(p/name);
    if (file.is_open())
    {
        cout << "--------------------------------\n";
        while (!file.eof())
        {
            char buff[1024];
            file.getline(buff, 1023);
            cout << buff <<"\n";
        }
        cout << "--------------------------------\n";
        file.close();
    }
    else
    {
        cout << "Невозможно открыть" << p << name <<"\n";
    }
}

int main(int argс, char* argv[]) // включим аргументы командной строки для принятия пути каталога, из которого начнет работать программа
{
	fs::path p = fs::current_path(); //инифиализируем объект для навигации по файловой системе
    p = "C:\\1\\"; // путь по умолчанию
    if (argс == 2) // если передан аргумент - присваиваем его родительскому пути
	{
		p = fs::path(argv[1]);
	}
  
	system("chcp 1251 > 0");
    int opt{ -1 }; //хранения опции меню
    HardDisk H; // структура для отображения информации о жестких дисках
    while (opt != 0)
    {
        //system("cls");
        string temp;
        cout << "Вы находитесь:\n" << p.parent_path() << "\n";
       
        //менюшечка
        cout << "\n" <<
        "1 - Смена текущего каталога (путь к текущему каталогу должен всегда отображаться на экране)\n"
            "2 - Отображение подключенных жетских дисков\n"
            "3 - Отображение содержания текущего каталога\n"
            "4 - Создание нового каталога в текущем каталоге\n"
            "5 - Удаление уже существующего каталога и его сожержимого\n"
            "6 -  \n"
            "7 - Удаление файла из текущего каталога\n"
            "8 - Переименование файла в текущем каталоге\n"
            "9 - Перемещение файла из текущего каталога в указанный пользователем каталог\n"
            "10 - Вывод содержимого указанного пользователем файла из текущего каталога на экран\n"
            "0 - Выход\n";
        std::cin >> opt; // ввод выбора меню


        switch (opt)
        {
        case 1:
            cout << "Введи полное имя пути\n";
            cin >> p;
            break;
        case 2:
                
            cout << "HardDisk:";
            for (auto p : H.lst)
            {
                cout << p.name;
                cout << " - " << p.type;
                cout << "\n";
            }
            break;
        case 3:
            for (auto c : fs::directory_iterator(p))
            {
                if (c.is_directory()) {
                    cout << c << " - папка";
                }
                cout << c << " - файл";
                cout << "\n";
            }
            cout << "\n-------------------------------------\n";
            system("pause");
            break;
        case 4:
            cout << "Введите имя новой директории\n";
            cin >> temp;
            Create_dir(p, temp);
            break;
        case 5:
            Remoove_dir(p);
            p = p.root_directory();
            break;
        case 6:
            break;
        case 7:
            cout << "Введите имя файла для удаления\n";
            cin >> temp;
            Remoove_file(p, temp);
            break;
        case 8:
            Rename(p);
            break;
        case 9:
            Moove(p);
            break;
        case 10:
            Read(p);
            break;
        default:
            break;
        }
    }
   
   
	cout << "\n" << p.root_path();
}