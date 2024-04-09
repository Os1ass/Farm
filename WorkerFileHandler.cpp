#include "WorkerFileHandler.h"

void WorkerFileHandler::initUsersList()
{
	if (!checkFile())
		return;

	ifstream file(filename);
	string line;
	stringstream lineStream;
	while (getline(file, line))
	{
		lineStream << line;
		User* curUser = new Worker();
		lineStream >> curUser;
		lineStream.clear();
		usersList.push_back(curUser);
	}
	file.close();
}

vector<Worker*> WorkerFileHandler::getWorkersList()
{
	vector<Worker*> workersList;
	for (auto worker : usersList)
		workersList.emplace_back(static_cast<Worker*>(worker));
	return workersList;
}

void WorkerFileHandler::printUsers()
{
	if (usersList.size() == 0)
	{
		cout << "Нет учетных записей\n";
		return;
	}
	sort(usersList.begin(), usersList.end(),
		[](User const* const a, User const* const b) { return *a < *b; });
	Worker::printTableHeader();
	int index = 0;
	for (auto user : usersList)
	{
		user->tablePrint(index);
		index++;
		//cout << endl;
	}
}
