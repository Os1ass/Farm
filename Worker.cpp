#include "Worker.h"

string getProfessionName(Profession profession)
{
    switch (profession)
    {
    case milker: return "������";
    case tractorDriver: return "����������";
    case combineDriver: return "���������";
    case herder: return "������";
    default: return "����������� ���������";
    }
}

void Worker::printWorkDays()
{
    if (production.empty())
    {
        cout << "\n��������� ��� ���\n";
        return;
    }
    cout << endl
        << "+----+------------+--------------------------------+------------------+\n"
        << "| No |    ����    |  ���������� ����������� ������ | �������� �� ���� |\n"
        << "+----+------------+--------------------------------+------------------+\n";

    int size = production.size();
    auto iterator = production.begin();
    string workString = getWorkString();
    int amount, salary;
    for (int i = 0; i < size; i++, iterator++)
    {
        amount = (*iterator).second.first;
        salary = (*iterator).second.second;
        cout << (i < 10 ? "|  " : "| ") << i + 1
            << " | " << (*iterator).first.getDateString()
            << " | " << setw(27) << workString
            << (amount < 100 ? "0" : "") << (amount < 10 ? "0" : "") << to_string(amount)
            << " | " << setw(16) << (salary != 0 ? to_string(salary) + "$" : "�� ���������")
            << " |\n";
        cout << "+----+------------+--------------------------------+------------------+\n";
    }
}

void Worker::printUnpaidWorkDays()
{
    if (production.empty() || getNumberUnpaidWorkDays() == 0)
    {
        cout << "\n��������� ���\n";
        return;
    }
    cout << endl
        << "+----+------------+--------------------------------+------------------+\n"
        << "| No |    ����    |  ���������� ����������� ������ | �������� �� ���� |\n"
        << "+----+------------+--------------------------------+------------------+\n";

    int size = production.size();
    auto iterator = production.begin();
    string workString = getWorkString();
    int amount, salary, index = 0;
    for (int i = 0; i < size; i++, iterator++)
    {
        amount = (*iterator).second.first;
        salary = (*iterator).second.second;
        if (salary != 0)
            continue;
        index++;
        cout << "| " << setw(2) << index
            << " | " << (*iterator).first.getDateString()
            << " | " << setw(27) << workString
            << (amount < 100 ? "0" : "") << (amount < 10 ? "0" : "") << to_string(amount)
            << " | " << setw(16) << (salary != 0 ? to_string(salary) + "$" : "�� ���������")
            << " |\n";
        cout << "+----+------------+--------------------------------+------------------+\n";
    }
}

void Worker::setSalary(int index, int salary)
{
    Date date = getUnpaidWorkDayDate(index);
    setSalaryByDate(date, salary);
}

string Worker::getWorkString()
{
    string ret;
    switch (profession)
    {
    case milker:
        ret = "������� ������ ������: ";
        break;
    case tractorDriver:
        ret = "���������� �������� �����: ";
        break;
    case combineDriver:
        ret = "������� �������� �����: ";
        break;
    case herder:
        ret = "�������� �����: ";
        break;
    default:
        ret = "����������� ��������� ";
        break;
    }
    return ret;
}

int Worker::getAmountByDate(Date date)
{
    if (production.find(date) == production.end())
        return -1;
    return production[date].first;
}

int Worker::getNumberUnpaidWorkDays()
{
    int ret = 0;
    int size = production.size();
    auto iterator = production.begin();
    for (int i = 0; i < size; i++, iterator++)
        if ((*iterator).second.second == 0)
            ret++;
    return ret;
}

Date Worker::getUnpaidWorkDayDate(int index)
{
    auto iterator = production.begin();
    while (iterator != production.end())
    {
        while (iterator != production.end() && (*iterator).second.second != 0) iterator++;
        if (iterator == production.end())
            break;

        if (index == 0)
            break;
        index--;
        iterator++;
    }
    if (iterator == production.end())
        return Date();
    return (*iterator).first;
}

int Worker::getAmountOfWork(Date begin, Date end)
{
    int amount = 0;
    auto iterator = production.begin();
    Date curDate;
    while (iterator != production.end())
    {
        curDate = (*iterator).first;
        if (curDate >= begin && curDate <= end)
            amount += (*iterator).second.first;
        iterator++;
    }
    return amount;
}

void Worker::setSalaryByDate(Date date, int salary)
{
    if (production.find(date) == production.end())
        return;
    production[date].second = salary;
}

void Worker::doWork(Date date, int amountOfWork)
{
    production[date] = make_pair(amountOfWork, 0);
}

void Worker::registration()
{
    User::registration();
    int profession;
    cout << "��������� ���������:\n"
        << "1 - ������\n"
        << "2 - ����������\n"
        << "3 - ���������\n"
        << "4 - ������\n";
    do {
        cout << "������� ��� �����: ";
        cin >> profession;
    } while (profession < 0 || profession > 4);
    this->profession = Profession(profession);
}

void Worker::print()
{
    User::print();
    cout << "���������: "; cout << getProfessionName(profession);
}

void Worker::tablePrint(int index)
{
    cout << (index < 10 ? "|  " : "| ") << index + 1 << " | " << setw(17) << name
        << " | " << setw(9) << login
        << " |   " << birthDate.getDateString()
        << "  | " << setw(7) << sex
        << " | " << setw(16) << phoneNumber 
        << " | " << setw(21) << getProfessionName(profession) << " |\n";
    cout << "+----+-------------------+-----------+---------------+---------+------------------+-----------------------+\n";
}

void Worker::printTableHeader()
{
    cout << endl
        << "+----+-------------------+-----------+---------------+---------+------------------+-----------------------+\n"
        << "| No |        ���        |   �����   | ���� �������� |   ���   | ���������� ����� |       ���������       |\n"
        << "+----+-------------------+-----------+---------------+---------+------------------+-----------------------+\n";
}

ostream& Worker::getDataStream(ostream& output) const
{
    User::getDataStream(output);
    output << to_string(profession) + '|';
    auto iterator = production.begin();
    for (int i = 0; i < production.size(); i++, iterator++)
    {
        output << (*iterator).first.getDateString() << "-"
            << (*iterator).second.first << "-"
            << (*iterator).second.second << "-";
        if (i != production.size() - 1)
            output << '/';
    }
    output << '|';
    return output;
}

istream& Worker::setDataFromStream(istream& input)
{
    User::setDataFromStream(input);
    string profession;
    if (!getline(input, profession, '|')) {
        input.setstate(ios::failbit);
        return input;
    }
    this->profession = Profession(stoi(profession));
    string production, date, amount, salary;
    getline(input, production, '|');
    stringstream productionStream;
    productionStream << production;
    while (productionStream.peek() <= '9' && productionStream.peek() >= '0')
    {
        getline(productionStream, date, '-');
        getline(productionStream, amount, '-');
        getline(productionStream, salary, '/');
        this->production[Date(date)] = make_pair(stoi(amount), stoi(salary));
    }
    return input;
}
