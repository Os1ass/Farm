#include "Report.h"

Report::Report(string report)
{
    number = purchasesCost = salariesSum = 0;
    stringstream input;
    input << report;
    input >> this;
}

void Report::initByConsole(vector<Accountant*> accountants, vector<Worker*> workers)
{
    /*cout << "������� �������� ������: ";
    if (cin.peek() == '\n')
        cin.get();
    getline(cin, name);*/
    cout << "���� ������ ������\n";
    begin.readDate();
    cout << "���� ����� ������\n";
    do {
        end.readDate();
    } while (begin > end);
    amountOfWorkByProfessions.resize(PROFESSIONSIZE);
    for (auto accountant : accountants)
    {
        salariesSum += accountant->getSalariesSum(begin, end);
        purchasesCost += accountant->getPurchasesCost(begin, end);
    }
    for (auto worker : workers)
        amountOfWorkByProfessions[worker->getProfession()] += worker->getAmountOfWork(begin, end);
}

string Report::getReportString() const
{
    return to_string(number) + '-' +
        begin.getDateString() + '-' +
        end.getDateString() + '-' +
        to_string(amountOfWorkByProfessions[milker]) + '-' +
        to_string(amountOfWorkByProfessions[combineDriver]) + '-' +
        to_string(amountOfWorkByProfessions[tractorDriver]) + '-' +
        to_string(amountOfWorkByProfessions[herder]) + '-' +
        to_string(purchasesCost) + '-' +
        to_string(salariesSum);
}

void Report::print()
{
    cout << "� ������ � " << begin.getDateString() << " �� " << end.getDateString();
    cout << "\n������� " << amountOfWorkByProfessions[milker] << " ������ ������\n";
    cout << "������� " << amountOfWorkByProfessions[combineDriver] << " �� �����\n";
    cout << "���������� " << amountOfWorkByProfessions[tractorDriver] << " �� �����\n";
    cout << "�������� " << amountOfWorkByProfessions[herder] << " ��������\n";
    cout << "����� ������� ��������� " << Purchase::getPriceString(purchasesCost);
    cout << "\n���������� ��������� " << Purchase::getPriceString(salariesSum) << endl;
}

void Report::tablePrint(int index)
{
    cout
        << "| " << setw(2) << index
        << " |   " << begin.getDateString()
        << "  |  " << end.getDateString()
        << "  | " << setw(16) << amountOfWorkByProfessions[milker] << " �"
        << " | " << setw(10) << amountOfWorkByProfessions[combineDriver] << " ��"
        << " | " << setw(13) << amountOfWorkByProfessions[tractorDriver] << " ��"
        << " | " << setw(14) << amountOfWorkByProfessions[herder]
        << " | " << setw(8) << Purchase::getPriceString(purchasesCost)
        << " | " << setw(8) << Purchase::getPriceString(salariesSum) << " |\n";
    cout << "+----+---------------+--------------+--------------------+---------------+------------------+----------------+----------+----------+\n";
}

void Report::skipSeparators(istream& input)
{
    while (input.peek() == ' ' || input.peek() == '|')
        input.get();
}

void Report::printTableHeader()
{
    printTableHeader(cout);
}

void Report::printTableHeader(ostream& output)
{
    output
        << "+----+---------------+--------------+--------------------+---------------+------------------+----------------+----------+----------+" << endl
        << "| No | ������ ������ | ����� ������ | ����������� ������ | ������� ����� | ���������� ����� | �������� ����� |  ������� | �������� |" << endl
        << "+----+---------------+--------------+--------------------+---------------+------------------+----------------+----------+----------+" << endl;
}

ostream& operator<<(ostream& output, const Report* report)
{
    output
        << "| " << setw(2) << report->number
        << " |   " << report->begin.getDateString()
        << "  |  " << report->end.getDateString()
        << "  | " << setw(16) << report->amountOfWorkByProfessions[milker] << " �"
        << " | " << setw(10) << report->amountOfWorkByProfessions[combineDriver] << " ��"
        << " | " << setw(13) << report->amountOfWorkByProfessions[tractorDriver] << " ��"
        << " | " << setw(14) << report->amountOfWorkByProfessions[herder]
        << " | " << setw(8) << Purchase::getPriceString(report->purchasesCost)
        << " | " << setw(8) << Purchase::getPriceString(report->salariesSum) << " |" << endl;
    output << "+----+---------------+--------------+--------------------+---------------+------------------+----------------+----------+----------+" << endl;
    return output;
}

istream& operator>>(istream& input, Report* report)
{
    string number, begin, end, amount, cost, buf;
    Report::skipSeparators(input);
    if (!getline(input, number, '-')) {
        input.setstate(ios::failbit);
        return input;
    }
    report->amountOfWorkByProfessions.resize(PROFESSIONSIZE);
    report->number = stoi(number);
    //Report::skipSeparators(input);
    getline(input, begin, '-');
    report->begin = Date(begin);
    //Report::skipSeparators(input);
    getline(input, end, '-');
    report->end = Date(end);
    //Report::skipSeparators(input);
    getline(input, amount, '-');
    report->amountOfWorkByProfessions[milker] = stoi(amount);
    //input.get(); input.get();
    //Report::skipSeparators(input);
    getline(input, amount, '-');
    report->amountOfWorkByProfessions[combineDriver] = stoi(amount);
    //input.get(); input.get(); input.get();
    //Report::skipSeparators(input);
    getline(input, amount, '-');
    report->amountOfWorkByProfessions[tractorDriver] = stoi(amount);
    //input.get(); input.get(); input.get();
    //Report::skipSeparators(input);
    getline(input, amount, '-');
    report->amountOfWorkByProfessions[herder] = stoi(amount);
    //Report::skipSeparators(input);
    getline(input, cost, '-');
    report->purchasesCost = stoi(cost);
    //Report::skipSeparators(input);
    getline(input, cost);
    report->salariesSum = stoi(cost);
    //getline(input, buf);
    return input;
}
