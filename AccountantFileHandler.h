#pragma once
#include "FileHandler.h"
#include "Accountant.h"

//����� ��������� ����� � �������� � �����������
class AccountantFileHandler : public FileHandler
{
private:
	virtual void initUsersList() override;	//���������� ������ ������������� ������ ������������� �� �����

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

	vector<Accountant*> getAccountantsList();	//�������� ������ �������������, ����������� � Accountant*	
	void printUsers();							//����� �������������
};