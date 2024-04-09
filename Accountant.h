#pragma once
#include "Worker.h"
#include "Purchase.h"

//Класс бухгалтера, наследованный от абстрактного класса пользователя
class Accountant : public User
{
private:
	vector<Purchase*> purchases;			//Закупки
	multimap<Date, pair<int, int>> salaries;//Выплаченные зарплаты

public:
	Accountant() : User() {}

	int getSalariesSum(Date begin, Date end);	//Получить сумму выплаченных зарплат в период с begin до end
	int getPurchasesCost(Date begin, Date end);	//получить сумму закупок, совершенных в период с begin дл end

	void addPurchase(Purchase* purchase);				//Добавить закупку
	void addSalary(Date date, int workerId, int salary);//Добавить выплаченную зарплату

	void printPurchases();						//Вывести закупки
	void printSalaries(vector<Worker*> workers);//Вывести выплаченные зарплаты

	void tablePrint(int index) override;			//Табличный вывод в строку с индексом index
	ostream& getDataStream(ostream& output) const;	//Вывод данных в выходной поток
	istream& setDataFromStream(istream& input);		//Чтение данных из входного потока

	~Accountant() { purchases.clear(); salaries.clear(); }
};