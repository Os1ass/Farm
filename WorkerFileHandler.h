#pragma once
#include "FileHandler.h"
#include "Worker.h"

//Класс обработки файла с записями о рабочих
class WorkerFileHandler : public FileHandler
{
private:
	virtual void initUsersList() override;	//Перегрузка метода инициализации списка пользователей из файла

public:
	WorkerFileHandler() : FileHandler() {};
	WorkerFileHandler(string filename)
		: FileHandler(filename) {
		initUsersList();
	}
	WorkerFileHandler(string filename, int userId)
		: FileHandler(filename, userId) {
		initUsersList();
	}

	vector<Worker*> getWorkersList();		//Получить список пользователей, приведенных к Worker*
	void printUsers();						//Вывод пользователей
};