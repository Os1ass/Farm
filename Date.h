#pragma once
#include <iostream>
#include <string>

using namespace std;

//������� ������ ����� �� �������
int readNumber();

//����� ����
class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date();
	Date(string date);		//����������� �� ������ ���� 01.01.2001

	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }

	void setDay(int day) { this->day = day; }
	void setMonth(int month) { this->month = month; }
	void setYear(int year) { this->year = year; }

	static string getCurrentDate();		//����������� �����, ������������ ������� ����

	static bool isCorrectDate(int day, int month, int year);			//����������� ����� �������� ���� �� ������������
	bool isCorrectDate() { return isCorrectDate(day, month, year); }	//����� �������� ������� ���� �� ������������

	void readDate();			//����� ������ ���� �� �������(����������� ������� ���� ��� ������� ����)
	bool init(string date);		//������������� �� ������
	void initByConsole();		//������������� � �������

	string getDateString() const;	//���� ����� ������ ���� 01.01.2001

	friend const Date& operator++(Date& date);
	friend bool operator== (const Date& date1, const Date& date2);
	friend bool operator<= (const Date& date1, const Date& date2);
	friend bool operator>= (const Date& date1, const Date& date2);
	friend bool operator< (const Date& date1, const Date& date2);
	friend bool operator> (const Date& date1, const Date& date2);
};