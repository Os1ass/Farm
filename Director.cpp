#include "Director.h"

void Director::getReport(vector<Accountant*> accountants, vector<Worker*> workers)
{
	Report* report = new Report();
	report->initByConsole(accountants, workers);
	report->setNumber(reports.size() + 1);
	addReport(report);
	//ofstream fout("report.txt", ios::trunc);
	ofstream fout("report.txt", ios::app);
	//Report::printTableHeader(fout);
	fout << report;
	fout.close();
	report->print();
	cout << "Отчет записан в report.txt\n";
}

void Director::addReport(Report* report)
{
	reports.emplace_back(report);
}

void Director::printReports()
{
	if (reports.size() == 0)
	{
		cout << "Нет отчетов\n";
		return;
	}
	Report::printTableHeader();
	for (auto report : reports)
		cout << report;
}

void Director::tablePrint(int index)
{
	cout << (index < 10 ? "|  " : "| ") << index + 1 << " | " << setw(17) << name
		<< " | " << setw(9) << login
		<< " |   " << birthDate.getDateString()
		<< "  | " << setw(7) << sex
		<< " | " << setw(16) << phoneNumber << " |\n";
	cout << "+----+-------------------+-----------+---------------+---------+------------------+\n";
}

ostream& Director::getDataStream(ostream& output) const
{
    User::getDataStream(output);
	for (int i = 0; i < reports.size(); i++)
	{
		output << reports[i]->getReportString();
		if (i != reports.size() - 1)
			output << '/';
	}
	output << '|';
	return output;
}

istream& Director::setDataFromStream(istream& input)
{
    User::setDataFromStream(input);
	string allReports;
	getline(input, allReports, '|');
	stringstream reportsStream;
	reportsStream << allReports;
	string report;
	while (getline(reportsStream, report, '/'))
		reports.emplace_back(new Report(report));
	return input;
}
