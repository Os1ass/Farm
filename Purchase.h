#pragma once
#include "Date.h"
#include <iomanip>

//����� �������
class Purchase
{
private:
	Date date;		//���� �������
	string product;	//�����
	int amount;		//���-��
	int price;		//����

public:
	Purchase() { amount = 0; price = 0; }
	Purchase(Date date, string product, int amount, int price);

	void initByConsole();	//������������� �� �������

	Date getDate() { return date; }
	string getProduct() { return product; }
	int getAmount() { return amount; }
	int getPrice() { return price; }

	static string getPriceString(int price);			//����������� �����, ������������ ���� ����� 100.000$
	static int getPriceFromString(string priceString);	//����������� �����, ������������ ����� �� ������ ���� 100.000$

	void setDate(Date date) { this->date = date; }
	void setProduct(string product) { this->product = product; }
	void setAmount(int amount) { this->amount = amount; }
	void setPrice(int price) { this->price = price; }

	void print();				//����� ���������� � �������
	void tablePrint(int index);	//����� ���������� � ������� ��� ������ �������(������ - ����� ������)

	static void printTableHeader();	//���������� �����, ��������� ����� ������� ��� ���������� ������

	friend ostream& operator<<(ostream& output, const Purchase* purchase);
	friend istream& operator>>(istream& input, Purchase* purchase);
};