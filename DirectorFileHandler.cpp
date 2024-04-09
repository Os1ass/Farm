#include "DirectorFileHandler.h"

void DirectorFileHandler::initUsersList()
{
	if (!checkFile())
		return;

	ifstream file(filename);
	string line;
	stringstream lineStream;
	while (getline(file, line))
	{
		lineStream << line;
		User* curUser = new Director();
		lineStream >> curUser;
		lineStream.clear();
		usersList.push_back(curUser);
	}
	file.close();
}

vector<Director*> DirectorFileHandler::getDirectorsList()
{
	vector<Director*> directorsList;
	for (auto director : usersList)
		directorsList.emplace_back(static_cast<Director*>(director));
	return directorsList;
}

void DirectorFileHandler::printUsers()
{
	if (usersList.size() == 0)
	{
		cout << "Нет учетных записей\n";
		return;
	}
	sort(usersList.begin(), usersList.end(),
		[](User const* const a, User const* const b) { return *a < *b; });
	Director::printTableHeader();
	int index = 0;
	for (auto user : usersList)
	{
		user->tablePrint(index);
		index++;
	}
}
