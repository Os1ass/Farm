#pragma once
#include <iostream>
#include <string>

using namespace std;

//Функция чтения числа из консоли
int readNumber();

//Класс даты
class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date();
	Date(string date);		//Конструктор из строки вида 01.01.2001

	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }

	void setDay(int day) { this->day = day; }
	void setMonth(int month) { this->month = month; }
	void setYear(int year) { this->year = year; }

	static string getCurrentDate();		//Статический метод, возвращающий текущую дату

	static bool isCorrectDate(int day, int month, int year);			//Статический метод проверка даты на корректность
	bool isCorrectDate() { return isCorrectDate(day, month, year); }	//Метод проверка обьекта даты на корректность

	void readDate();			//Метод чтения даты из консоли(возможность выбрать ввод или текущую дату)
	bool init(string date);		//Инициализация из строки
	void initByConsole();		//Инициализация с консоли

	string getDateString() const;	//Дата ввиде строки типа 01.01.2001

	friend const Date& operator++(Date& date);
	friend bool operator== (const Date& date1, const Date& date2);
	friend bool operator<= (const Date& date1, const Date& date2);
	friend bool operator>= (const Date& date1, const Date& date2);
	friend bool operator< (const Date& date1, const Date& date2);
	friend bool operator> (const Date& date1, const Date& date2);
};