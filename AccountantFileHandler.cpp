#include "AccountantFileHandler.h"

void AccountantFileHandler::initUsersList()
{
	if (!checkFile())
		return;

	ifstream file(filename);
	string line;
	stringstream lineStream;
	while (getline(file, line))
	{
		lineStream << line;
		User* curUser = new Accountant();
		lineStream >> curUser;
		lineStream.clear();
		usersList.push_back(curUser);
	}
	file.close();
}

vector<Accountant*> AccountantFileHandler::getAccountantsList()
{
	vector<Accountant*> accountantsList;
	for (auto accountant : usersList)
		accountantsList.emplace_back(static_cast<Accountant*>(accountant));
	return accountantsList;
}

void AccountantFileHandler::printUsers()
{
	if (usersList.size() == 0)
	{
		cout << "Нет учетных записей\n";
		return;
	}
	sort(usersList.begin(), usersList.end(),
		[](User const* const a, User const* const b) { return *a < *b; });
	Accountant::printTableHeader();
	int index = 0;
	for (auto user : usersList)
	{
		user->tablePrint(index);
		index++;
		//cout << endl;
	}
}
