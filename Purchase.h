#pragma once
#include "Date.h"
#include <iomanip>

//Класс закупки
class Purchase
{
private:
	Date date;		//Дата закупки
	string product;	//Товар
	int amount;		//Кол-во
	int price;		//Цена

public:
	Purchase() { amount = 0; price = 0; }
	Purchase(Date date, string product, int amount, int price);

	void initByConsole();	//Инициализация из консоли

	Date getDate() { return date; }
	string getProduct() { return product; }
	int getAmount() { return amount; }
	int getPrice() { return price; }

	static string getPriceString(int price);			//Статический метод, возвращающий цену ввиде 100.000$
	static int getPriceFromString(string priceString);	//Статический метод, возвращающий число из строки вида 100.000$

	void setDate(Date date) { this->date = date; }
	void setProduct(string product) { this->product = product; }
	void setAmount(int amount) { this->amount = amount; }
	void setPrice(int price) { this->price = price; }

	void print();				//Вывод информации о покупке
	void tablePrint(int index);	//Вывод информации о покупке как строка таблицы(индекс - номер строки)

	static void printTableHeader();	//Статиеский метод, выводящий шапку таблицы для табличного вывода

	friend ostream& operator<<(ostream& output, const Purchase* purchase);
	friend istream& operator>>(istream& input, Purchase* purchase);
};