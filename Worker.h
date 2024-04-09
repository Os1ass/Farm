#pragma once
#include "User.h"

//������������ ���������
static enum Profession {
	unknown,			//����������� ���������
	milker,             //������
	tractorDriver,      //����������
	combineDriver,      //���������
	herder,				//������
	PROFESSIONSIZE		//���������� ���������
};

//�������, ������������ �������� ���������
string getProfessionName(Profession profession);

//����� ��������, ������������� �� ������������ ������ ������������
class Worker : public User
{
private:
	Profession profession;
	map<Date, pair<int, int>> production;	//������������������ �� ����

public:
	Worker() : User() { profession = Profession(0); }

	void printWorkDays();					//����� ��������� �� ����
	void printUnpaidWorkDays();				//����� ������������ ����
	void setSalary(int index, int salary);	//���������� �������� �� ������� ����

	Profession getProfession() { return profession; }
	string getWorkString();						//�������� ������ � ����������� ������ � ����������� �� ���������
	int getAmountByDate(Date date);				//�������� ���������� ������ �� ����
	int getNumberUnpaidWorkDays();				//�������� ���������� ������������ ������� ����
	Date getUnpaidWorkDayDate(int index);		//�������� ������������ ������� ���� �� �������
	int getAmountOfWork(Date begin, Date end);	//�������� ���-�� ������ � ������ � begin �� end

	void setProfession(int profession) { this->profession = Profession(profession);  }
	void setSalaryByDate(Date date, int salary);	//���������� �������� �� ������� ���� �� ����

	void doWork(Date date, int amountOfWork);		//�������� ���������

	void registration();				//�����������
	void print();						//����� ���������� � �������
	void tablePrint(int index) override;//���������� ������������ ������ ���������� ������ �� ������ ������������
	
	static void printTableHeader();					//����������� ����� ������ ����� ������� � �������
	ostream& getDataStream(ostream& output) const;	//����������� ����� ��������� ������ �� �������
	istream& setDataFromStream(istream& input);		//����������� ����� ������ ������ �� �������

	~Worker() { production.clear(); }
};