#pragma once
#include "User.h"
#include "Report.h"
#include <fstream>

//Класс директора, наследованный от абстрактного класса пользователя
class Director : public User
{
private:
	vector<Report*> reports;	//Запрошенные отчеты

public:
	Director() : User() {}

	void getReport(vector<Accountant*> accountants, vector<Worker*> workers);	//Получить отчет
	void addReport(Report* report);												//Добавить отчет

	void printReports();	//Вывести запрошенные отчеты

	void tablePrint(int index) override;			//Табличный вывод в строку под номером index
	ostream& getDataStream(ostream& output) const;	//Вывести данные в выходной поток
	istream& setDataFromStream(istream& input);		//Получить данне из входного потока
};