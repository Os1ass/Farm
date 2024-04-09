#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

//������� ������������ ��� ������
//@return -1 - str1 < str2, 0 - str1 == str2, 2 - str1 > str2
int equals(string str1, string str2);

//������� ����� ��������� ����� � �������� �������������
class FileHandler
{
protected:
	int authorizedUserId;	//Id ��������������� ������������
	string filename;		//�������� �����
	vector<User*> usersList;//������ �������������

	bool checkFile();				//�������� �����
	int getFileSize();				//�������� ������ �����
	virtual void initUsersList() {}	//����������� ����� ������������� ������ �������������

public:
	FileHandler() { authorizedUserId = 0; }
	FileHandler(string filename);
	FileHandler(string filename, int userId);

	int getAuthorizedUserId() { return authorizedUserId; }
	vector<User*> getUsersList();

	void setAuthorizedUserId(int authorizedUserId) { this->authorizedUserId = authorizedUserId; }

	void addUser(User* user);	//�������� ����� � ������������
	bool removeUser(int id);	//������� ������ � ������������
	void save();				//��������� ���������� � ������������� � ����

	void editLogin(string login) { getAuthorizedUser()->setLogin(login); }
	void editPassword(string password) { getAuthorizedUser()->setPassword(password); }

	bool isRegistred(int id);		//�������� �� ������� ������������ � id � ������
	bool isRegistred(string login);	//�������� �� ������� ������������ � login � ������
	bool isAuthorized();			//������� ���� �� �������������� ������������

	vector<User*> searchUsersByName(string name);	//����� ������������ � ������ �� ���

	User* getAuthorizedUser();						//�������� ��������������� ������������
	User* getUserById(int id);						//�������� ������������ �� id
	User* getUserByPhoneNumber(string phoneNumber);	//�������� ������������ �� ������
	User* getUserByLogin(string login);				//�������� ������������ �� ������

	bool authorization(string login, string password);	//����������� ����������� � ������� login � ������� password

	void printAuthorizedUser();	//������� ��������������� ������������
	virtual void printUsers();	//������� ������ �������������
	/*void registration()
	{
		T newUser();
		newUser.registration();
	}*/

	~FileHandler() { save(); }
};