#pragma once
#include "Worker.h"
#include "Purchase.h"

//����� ����������, ������������� �� ������������ ������ ������������
class Accountant : public User
{
private:
	vector<Purchase*> purchases;			//�������
	multimap<Date, pair<int, int>> salaries;//����������� ��������

public:
	Accountant() : User() {}

	int getSalariesSum(Date begin, Date end);	//�������� ����� ����������� ������� � ������ � begin �� end
	int getPurchasesCost(Date begin, Date end);	//�������� ����� �������, ����������� � ������ � begin �� end

	void addPurchase(Purchase* purchase);				//�������� �������
	void addSalary(Date date, int workerId, int salary);//�������� ����������� ��������

	void printPurchases();						//������� �������
	void printSalaries(vector<Worker*> workers);//������� ����������� ��������

	void tablePrint(int index) override;			//��������� ����� � ������ � �������� index
	ostream& getDataStream(ostream& output) const;	//����� ������ � �������� �����
	istream& setDataFromStream(istream& input);		//������ ������ �� �������� ������

	~Accountant() { purchases.clear(); salaries.clear(); }
};