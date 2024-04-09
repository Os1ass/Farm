#pragma once
#include "FileHandler.h"
#include "Director.h"

//����� ��������� ����� � �������� � ����������
class DirectorFileHandler : public FileHandler
{
private:
	virtual void initUsersList() override;	//���������� ������ ������������� ������ ������������� �� �����

public:
	DirectorFileHandler() : FileHandler() {};
	DirectorFileHandler(string filename)
		: FileHandler(filename) {
		initUsersList();
	}
	DirectorFileHandler(string filename, int userId)
		: FileHandler(filename, userId) {
		initUsersList();
	}

	vector <Director*> getDirectorsList();	//�������� ������ �������������, ����������� � Director*
	void printUsers();						//����� �������������
};