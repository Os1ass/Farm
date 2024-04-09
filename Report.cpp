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
    /*cout << "Введите название отчета: ";
    if (cin.peek() == '\n')
        cin.get();
    getline(cin, name);*/
    cout << "Дата начала отчета\n";
    begin.readDate();
    cout << "Дата конца отчета\n";
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
    cout << "В период с " << begin.getDateString() << " до " << end.getDateString();
    cout << "\nПодоено " << amountOfWorkByProfessions[milker] << " литров молока\n";
    cout << "Собрано " << amountOfWorkByProfessions[combineDriver] << " кг зерна\n";
    cout << "Перевезено " << amountOfWorkByProfessions[tractorDriver] << " кг зерна\n";
    cout << "Выпасено " << amountOfWorkByProfessions[herder] << " животных\n";
    cout << "Сумма закупок составила " << Purchase::getPriceString(purchasesCost);
    cout << "\nЗарплатами выплачено " << Purchase::getPriceString(salariesSum) << endl;
}

void Report::tablePrint(int index)
{
    cout
        << "| " << setw(2) << index
        << " |   " << begin.getDateString()
        << "  |  " << end.getDateString()
        << "  | " << setw(16) << amountOfWorkByProfessions[milker] << " л"
        << " | " << setw(10) << amountOfWorkByProfessions[combineDriver] << " кг"
        << " | " << setw(13) << amountOfWorkByProfessions[tractorDriver] << " кг"
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
        << "| No | Начало отчета | Конец отчета | Произведено молока | Собрано зерна | Перевезено зерна | Выпасено скота |  Закупки | Зарплаты |" << endl
        << "+----+---------------+--------------+--------------------+---------------+------------------+----------------+----------+----------+" << endl;
}

ostream& operator<<(ostream& output, const Report* report)
{
    output
        << "| " << setw(2) << report->number
        << " |   " << report->begin.getDateString()
        << "  |  " << report->end.getDateString()
        << "  | " << setw(16) << report->amountOfWorkByProfessions[milker] << " л"
        << " | " << setw(10) << report->amountOfWorkByProfessions[combineDriver] << " кг"
        << " | " << setw(13) << report->amountOfWorkByProfessions[tractorDriver] << " кг"
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
