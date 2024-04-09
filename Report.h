#pragma once
#include "Accountant.h"
#include "Worker.h"
#include <vector>

//Класс отчета
class Report
{
private:
	//string name;
	int number;								//Номер отчета
	vector<int> amountOfWorkByProfessions;	//Кол-во работы по профессиям
	Date begin;								//Дата начала отчета
	Date end;								//Дата конца отчета
	int salariesSum;						//Сумма выплаченных зарплат
	int purchasesCost;						//Сумма закупок

public:
	Report() { number = salariesSum = purchasesCost = 0; }
	Report(string report);	//Инициализация из строки

	void initByConsole(vector<Accountant*> accountants, vector<Worker*> workers);	//Инициализация из консоли

	//string getName() { return name; }
	int getNumber() { return number; }
	vector<int> getAmountOfWork() { return amountOfWorkByProfessions; }
	Date getBeginDate() { return begin; }
	Date getEndDate() { return end; }
	int getSalariesSum() { return salariesSum; }
	int getPurchasesCost() { return purchasesCost; }

	string getReportString() const;	//Метод, возвращающий отчет ввиде строки с разделителями

	void setNumber(int number) { this->number = number; }
	//void setName(string name) { this->name = name; }
	void setAmountOfWork(vector<int> amountOfWorkByProfessions) { this->amountOfWorkByProfessions = amountOfWorkByProfessions; }
	void setBeginDate(Date begin) { this->begin = begin; }
	void setEndDate(Date end) { this->end = end; }
	void setSalariesSum(int salariesSum) { this->salariesSum = salariesSum; }
	void setPurchasesCost(int purchasesCost) { this->purchasesCost = purchasesCost; }

	void print();				//Вывод отчета
	void tablePrint(int index);	//Табличный вывод отчета строкой таблицы(индекс - номер строки)

	static void skipSeparators(istream& input);		//Статический метод, пропускающий разделители во входном потоке
	static void printTableHeader();					//Статический метод, выводящий шапку таблицы в консоль
	static void printTableHeader(ostream& output);	//Статический метод, выводящий шапку таблицы в заданный выходной поток

	friend ostream& operator<<(ostream& output, const Report* report);
	friend istream& operator>>(istream& input, Report* report);

};