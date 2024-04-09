#pragma once
#include <string>
#include <conio.h>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include "Date.h"

//#include "Menu.h"
using namespace std;

//абстрактный класс пользователя
class User
{
	friend class FileHandler;
public:
	User() { id = rand(); }	//Конструктор по умолчанию генерирует случайный id пользователя
	User(User* other);		//Конструктор копирования
	//bool compareTo(User* other);
	//void initByConsole();

	int getId();

	virtual void registration();			//Виртуальный метод регистрации
	virtual void print();					//Виртуальный метод вывода информации о пользователе
	virtual void tablePrint(int index) = 0;	//Абстрактный метод вывода информации в строку таблицы(индекс - номер строки)

	string getName() { return name; }
	string getSex() { return sex; }
	string getPhoneNumber() { return phoneNumber; }
	Date getBirthDate() { return birthDate; }

	void setName(string name) { this->name = name; }
	void setSex(string sex) { this->sex = sex; }
	void setPhoneNumber(string phoneNumber) { this->phoneNumber = phoneNumber; }
	void setBirthDate(Date birthDate) { this->birthDate = birthDate; }

	virtual ostream& getDataStream(ostream& output) const;	//Вывод информации о пользователе в выходной поток
	virtual istream& setDataFromStream(istream& input);		//Чтение информации о пользователе из входного потока

	static void printTableHeader();				//Статический метод вывода шапки таблицы в консоль
	static string getPassswordFromConsole();	//Статический метод получения пароля из консоли
	static string readPassword();				//Статический метод чтения пароля из консоли

	friend bool operator<(const User& left, const User& right);

protected:
	int id;
	string login;
	string password;
	string name;
	string sex;
	string phoneNumber;
	Date birthDate;

	void setLogin(string login) { this->login = login; }
	void setPassword(string password) { this->password = password; }

};

ostream& operator<<(ostream& output, const User* user);
istream& operator>>(istream& input, User* user);