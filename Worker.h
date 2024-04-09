#pragma once
#include "User.h"

//Перечисление профессий
static enum Profession {
	unknown,			//неизвестная профессия
	milker,             //доярка
	tractorDriver,      //тракторист
	combineDriver,      //комбайнер
	herder,				//пастух
	PROFESSIONSIZE		//количество профессий
};

//Функция, возвращающая название профессии
string getProfessionName(Profession profession);

//Класс рабочего, наследованный от абстрактного класса пользователя
class Worker : public User
{
private:
	Profession profession;
	map<Date, pair<int, int>> production;	//Производительность по дням

public:
	Worker() : User() { profession = Profession(0); }

	void printWorkDays();					//Вывод отработок по дням
	void printUnpaidWorkDays();				//Вывод неоплаченных дней
	void setSalary(int index, int salary);	//Установить зарплату за рабочий день

	Profession getProfession() { return profession; }
	string getWorkString();						//Получить строку о выполненной работе в зависимости от профессии
	int getAmountByDate(Date date);				//Получить количество работы по дате
	int getNumberUnpaidWorkDays();				//Получить количество неоплаченных рабочих дней
	Date getUnpaidWorkDayDate(int index);		//Получить неоплаченный рабочий день по индексу
	int getAmountOfWork(Date begin, Date end);	//Получить кол-во работы в период с begin до end

	void setProfession(int profession) { this->profession = Profession(profession);  }
	void setSalaryByDate(Date date, int salary);	//Установить запплату за рабочий день по дате

	void doWork(Date date, int amountOfWork);		//Добавить отработку

	void registration();				//Регистрация
	void print();						//Вывод информации о рабочем
	void tablePrint(int index) override;//перегрузка абстрактного метода табличного вывода из класса пользователя
	
	static void printTableHeader();					//Статический метод вывода шапки таблицы в консоль
	ostream& getDataStream(ostream& output) const;	//Статический метод получения пароля из консоли
	istream& setDataFromStream(istream& input);		//Статический метод чтения пароля из консоли

	~Worker() { production.clear(); }
};