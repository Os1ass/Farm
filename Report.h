#pragma once
#include "Accountant.h"
#include "Worker.h"
#include <vector>

//����� ������
class Report
{
private:
	//string name;
	int number;								//����� ������
	vector<int> amountOfWorkByProfessions;	//���-�� ������ �� ����������
	Date begin;								//���� ������ ������
	Date end;								//���� ����� ������
	int salariesSum;						//����� ����������� �������
	int purchasesCost;						//����� �������

public:
	Report() { number = salariesSum = purchasesCost = 0; }
	Report(string report);	//������������� �� ������

	void initByConsole(vector<Accountant*> accountants, vector<Worker*> workers);	//������������� �� �������

	//string getName() { return name; }
	int getNumber() { return number; }
	vector<int> getAmountOfWork() { return amountOfWorkByProfessions; }
	Date getBeginDate() { return begin; }
	Date getEndDate() { return end; }
	int getSalariesSum() { return salariesSum; }
	int getPurchasesCost() { return purchasesCost; }

	string getReportString() const;	//�����, ������������ ����� ����� ������ � �������������

	void setNumber(int number) { this->number = number; }
	//void setName(string name) { this->name = name; }
	void setAmountOfWork(vector<int> amountOfWorkByProfessions) { this->amountOfWorkByProfessions = amountOfWorkByProfessions; }
	void setBeginDate(Date begin) { this->begin = begin; }
	void setEndDate(Date end) { this->end = end; }
	void setSalariesSum(int salariesSum) { this->salariesSum = salariesSum; }
	void setPurchasesCost(int purchasesCost) { this->purchasesCost = purchasesCost; }

	void print();				//����� ������
	void tablePrint(int index);	//��������� ����� ������ ������� �������(������ - ����� ������)

	static void skipSeparators(istream& input);		//����������� �����, ������������ ����������� �� ������� ������
	static void printTableHeader();					//����������� �����, ��������� ����� ������� � �������
	static void printTableHeader(ostream& output);	//����������� �����, ��������� ����� ������� � �������� �������� �����

	friend ostream& operator<<(ostream& output, const Report* report);
	friend istream& operator>>(istream& input, Report* report);

};