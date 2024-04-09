#include "Accountant.h"

int Accountant::getSalariesSum(Date begin, Date end)
{
    int salariesSum = 0;
    auto iterator = salaries.begin();
    Date curDate;
    while (iterator != salaries.end())
    {
        curDate = (*iterator).first;
        if (curDate >= begin && curDate <= end)
            salariesSum += (*iterator).second.second;
        iterator++;
    }
    return salariesSum;
}

int Accountant::getPurchasesCost(Date begin, Date end)
{
    int purchasesCost = 0;
    Date curDate;
    for (auto purchase : purchases)
    {
        curDate = purchase->getDate();
        if (curDate >= begin && curDate <= end)
            purchasesCost += purchase->getPrice();
    }
    return purchasesCost;
}

void Accountant::addPurchase(Purchase* purchase)
{
    purchases.emplace_back(purchase);
}

void Accountant::addSalary(Date date, int workerId, int salary)
{
    salaries.insert(make_pair(date, make_pair(workerId, salary)));
}

void Accountant::printPurchases()
{
    if (purchases.empty())
    {
        cout << "\nБухгалтер еще не совершал закупок\n";
        return;
    }
    Purchase::printTableHeader();
    int index = 0;
    for (auto purchase : purchases)
        purchase->tablePrint(++index);
}

void Accountant::printSalaries(vector<Worker*> workers)
{
    if (salaries.empty())
    {
        cout << "\nБухгалтер еще не выдавал зарплат\n";
        return;
    }
    cout
        << "+----+------------+-------------------+--------------------------------+------------------+\n"
        << "|  № |    Дата    |   ФИО работника   |  Количество выполненной работы | Зарплата за день |\n"
        << "+----+------------+-------------------+--------------------------------+------------------+\n";

    int size = salaries.size(), workerId, amount;
    auto iterator = salaries.begin();
    bool workerFound;
    Date date;
    for (int i = 0; i < size; i++, iterator++)
    {
        workerFound = false;
        date = (*iterator).first;
        workerId = (*iterator).second.first;
        cout << "| " << setw(2) << i + 1
            << " | " << (*iterator).first.getDateString() << " | ";
        for (auto worker : workers)
            if (worker->getId() == workerId)
            {
                amount = worker->getAmountByDate(date);
                if (amount == -1)
                    break;
                cout << setw(17) << worker->getName()
                    << " | " << setw(27) << worker->getWorkString()
                    << setw(3) << to_string(amount)
                    << " | " << setw(16) << to_string((*iterator).second.second) + "$" << " |\n";
                worker->setSalaryByDate(date, (*iterator).second.second);
                workerFound = true;
                break;
            }
        if (!workerFound)
            cout << setw(71) << "Работник не найден|" << endl;
        cout << "+----+------------+-------------------+--------------------------------+------------------+\n";
    }
}

void Accountant::tablePrint(int index)
{
	cout << (index < 10 ? "|  " : "| ") << index + 1 << " | " << setw(17) << name
		<< " | " << setw(9) << login
		<< " |   " << birthDate.getDateString()
		<< "  | " << setw(7) << sex
		<< " | " << setw(16) << phoneNumber << " |\n";
	cout << "+----+-------------------+-----------+---------------+---------+------------------+\n";
}

ostream& Accountant::getDataStream(ostream& output) const
{
    User::getDataStream(output);
    int i = 0;
    for (auto purchase : purchases)
    {
        output << purchase;
        if (i++ != purchases.size() - 1)
            output << '/';
    }
    output << '|';
    auto iterator = salaries.begin();
    for (i = 0; i < salaries.size(); i++, iterator++)
    {
        output << (*iterator).first.getDateString() << "-"
            << (*iterator).second.first << "-"
            << (*iterator).second.second;
        if (i != salaries.size() - 1)
            output << '/';
    }
    output << '|';
    return output;
}

istream& Accountant::setDataFromStream(istream& input)
{
    User::setDataFromStream(input);
    string purchases, salaries, date, workerId, salary;
    stringstream purchasesStream, salariesStream;
    Purchase* purchase = new Purchase();
    getline(input, purchases, '|');
    purchasesStream << purchases;
    while (purchasesStream.peek() <= '9' && purchasesStream.peek() >= '0')
    {
        purchasesStream >> purchase;
        this->purchases.emplace_back(purchase);
    }
    getline(input, salaries, '|');
    salariesStream << salaries;
    while (salariesStream.peek() <= '9' && salariesStream.peek() >= '0')
    {
        getline(salariesStream, date, '-');
        getline(salariesStream, workerId, '-');
        getline(salariesStream, salary, '/');
        this->salaries.insert(make_pair(date, make_pair(stoi(workerId), stoi(salary))));
    }
    return input;
}
