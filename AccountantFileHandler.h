#pragma once
#include "FileHandler.h"
#include "Accountant.h"

//Класс обработки файла с записями о бухгалтерах
class AccountantFileHandler : public FileHandler
{
private:
	virtual void initUsersList() override;	//Перегрузка метода инициализации списка пользователей из файла

public:
	AccountantFileHandler() : FileHandler() {};
	AccountantFileHandler(string filename)
		: FileHandler(filename) {
		initUsersList();
	}
	AccountantFileHandler(string filename, int userId)
		: FileHandler(filename, userId) {
		initUsersList();
	}

	vector<Accountant*> getAccountantsList();	//Получить список пользователей, приведенных к Accountant*	
	void printUsers();							//Вывод пользователей
};