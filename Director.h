#pragma once
#include "User.h"
#include "Report.h"
#include <fstream>

//����� ���������, ������������� �� ������������ ������ ������������
class Director : public User
{
private:
	vector<Report*> reports;	//����������� ������

public:
	Director() : User() {}

	void getReport(vector<Accountant*> accountants, vector<Worker*> workers);	//�������� �����
	void addReport(Report* report);												//�������� �����

	void printReports();	//������� ����������� ������

	void tablePrint(int index) override;			//��������� ����� � ������ ��� ������� index
	ostream& getDataStream(ostream& output) const;	//������� ������ � �������� �����
	istream& setDataFromStream(istream& input);		//�������� ����� �� �������� ������
};