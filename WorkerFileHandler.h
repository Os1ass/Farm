#pragma once
#include "FileHandler.h"
#include "Worker.h"

//����� ��������� ����� � �������� � �������
class WorkerFileHandler : public FileHandler
{
private:
	virtual void initUsersList() override;	//���������� ������ ������������� ������ ������������� �� �����

public:
	WorkerFileHandler() : FileHandler() {};
	WorkerFileHandler(string filename)
		: FileHandler(filename) {
		initUsersList();
	}
	WorkerFileHandler(string filename, int userId)
		: FileHandler(filename, userId) {
		initUsersList();
	}

	vector<Worker*> getWorkersList();		//�������� ������ �������������, ����������� � Worker*
	void printUsers();						//����� �������������
};