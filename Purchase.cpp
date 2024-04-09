#include "Purchase.h"

Purchase::Purchase(Date date, string product, int amount, int price)
{
    this->date = date;
    this->product = product;
    this->amount = amount;
    this->price = price;
}

void Purchase::initByConsole()
{
    date.readDate();
    cout << "Введите название товара: ";
    if (cin.peek() == '\n')
        cin.get();
    getline(cin, product);
    cout << "Введите количество товара: "; cin >> amount;
    cout << "Введите цену закупки: "; cin >> price;
}

string Purchase::getPriceString(int price)
{
    string ret;
    if (price > 999)
        ret = to_string(price / 1000) + '.';
    ret += to_string((price % 1000) / 100);
    ret += to_string((price % 100) / 10);
    ret += to_string(price % 10);
    ret += '$';
    return ret;
}

int Purchase::getPriceFromString(string priceString)
{
    string th = "0";
    int i = 0;
    while (i < priceString.length() &&
        priceString[i] != '$' && priceString[i] != '.')
        th += priceString[i++];
    if (i == priceString.length())
        return 0;
    if (priceString[i] == '$')
        return stoi(th);
    string un = "0";
    while (i < priceString.length() && priceString[i] != '$')
        un += priceString[i++];
    if (i == priceString.length())
        return 0;
    return stoi(th) * 1000 + stoi(un);
}

void Purchase::print()
{
    cout << "Дата покупки: " << date.getDateString();
    cout << "\nПокупаемый товар: " << product;
    cout << "\nКоличество товара: " << amount;
    cout << "\nЦена покупки: " << price;
}

void Purchase::tablePrint(int index)
{
    cout << (index < 10 ? "|  " : "| ") << index + 1
        << " |  " << date.getDateString()
        << "  | " << setw(11) << product
        << " |     " << setw(4) << to_string(amount)
        << "   | " << setw(8) << getPriceString(price) << " |\n";
    cout << "+----+--------------+-------------+------------+----------+\n";
}

void Purchase::printTableHeader()
{
    cout
        << "+----+--------------+-------------+------------+----------+\n"
        << "| No | Дата покупки |    Товар    | Количество |   Цена   |\n"
        << "+----+--------------+-------------+------------+----------+\n";
}

ostream& operator<<(ostream& output, const Purchase* purchase)
{
    output << purchase->date.getDateString() << "-"
        << purchase->product << "-"
        << to_string(purchase->amount) << "-"
        << to_string(purchase->price);
    return output;
}

istream& operator>>(istream& input, Purchase* purchase)
{
    string date;
    if (!getline(input, date, '-')) {
        input.setstate(ios::failbit);
        return input;
    }
    purchase->date = Date(date);
    getline(input, purchase->product, '-');
    string amount;
    getline(input, amount, '-');
    purchase->amount = stoi(amount);
    string price;
    getline(input, price);
    purchase->price = stoi(price);

    return input;
}
