#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

//Функция сравнивающая две строки
//@return -1 - str1 < str2, 0 - str1 == str2, 2 - str1 > str2
int equals(string str1, string str2);

//Базовый класс обработки файла с записями пользователей
class FileHandler
{
protected:
	int authorizedUserId;	//Id авторизованного пользователя
	string filename;		//Название файла
	vector<User*> usersList;//Список пользователей

	bool checkFile();				//Проверка файла
	int getFileSize();				//Получить размер файла
	virtual void initUsersList() {}	//Виртуальный метод инициализации списка пользователей

public:
	FileHandler() { authorizedUserId = 0; }
	FileHandler(string filename);
	FileHandler(string filename, int userId);

	int getAuthorizedUserId() { return authorizedUserId; }
	vector<User*> getUsersList();

	void setAuthorizedUserId(int authorizedUserId) { this->authorizedUserId = authorizedUserId; }

	void addUser(User* user);	//Добавить зпись о пользователе
	bool removeUser(int id);	//Удалить запись о пользователе
	void save();				//Сохранить информацию о пользователях в файл

	void editLogin(string login) { getAuthorizedUser()->setLogin(login); }
	void editPassword(string password) { getAuthorizedUser()->setPassword(password); }

	bool isRegistred(int id);		//Проверка на наличие пользователя с id в списке
	bool isRegistred(string login);	//Проверка на наличие пользователя с login в списке
	bool isAuthorized();			//Проерка есть ли авторизованный пользователь

	vector<User*> searchUsersByName(string name);	//Поиск пользователя в списке по ФИО

	User* getAuthorizedUser();						//Получить авторизованного пользователя
	User* getUserById(int id);						//Получить пользователя по id
	User* getUserByPhoneNumber(string phoneNumber);	//Получить пользователя по номеру
	User* getUserByLogin(string login);				//Получить пользователя по логину

	bool authorization(string login, string password);	//Авторизация пользоателя с логином login и паролем password

	void printAuthorizedUser();	//Вывести авторизованного пользователя
	virtual void printUsers();	//Вывести список пользователей
	/*void registration()
	{
		T newUser();
		newUser.registration();
	}*/

	~FileHandler() { save(); }
};