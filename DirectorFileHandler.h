#pragma once
#include "FileHandler.h"
#include "Director.h"

//Класс обработки файла с записями о директорах
class DirectorFileHandler : public FileHandler
{
private:
	virtual void initUsersList() override;	//Перегрузка метода инициализации списка пользователей из файла

public:
	DirectorFileHandler() : FileHandler() {};
	DirectorFileHandler(string filename)
		: FileHandler(filename) {
		initUsersList();
	}
	DirectorFileHandler(string filename, int userId)
		: FileHandler(filename, userId) {
		initUsersList();
	}

	vector <Director*> getDirectorsList();	//Получить список пользователей, приведенных к Director*
	void printUsers();						//Вывод пользователей
};