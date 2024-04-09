#include "Menu.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    Menu* menu = new Menu(true);

    shared_ptr<FileHandler> fH = nullptr;
    MenuOption option1("Войти как рабочий", [&](shared_ptr<FileHandler> fH) {
        shared_ptr<Menu> workerMenu = createWorkerMenu();
        workerMenu->run();
        });
    MenuOption option2("Войти как бухгалтер", [&](shared_ptr<FileHandler> fH) {
        shared_ptr<Menu> accountantMenu = createAccountantMenu();
        accountantMenu->run();
        });
    MenuOption option3("Войти как директор", [&](shared_ptr<FileHandler> fH) {
        shared_ptr<Menu> directorMenu = createDirectorMenu();
        directorMenu->run();
        });
    MenuOption option4("Создать аккаунт", [&](shared_ptr<FileHandler> fH) {
        User* newUser = new Worker();
        newUser->registration();
        newUser->print();
        cout << endl;
        FileHandler* workerFileHandler = new WorkerFileHandler("workers");
        workerFileHandler->addUser(newUser);
        workerFileHandler->save();
        delete workerFileHandler;
        delete newUser;
        system("pause");
        });

    menu->addOption(option1);
    menu->addOption(option2);
    menu->addOption(option3);
    menu->addOption(option4);
    menu->run();
    /*FileHandler* workerFileHandler = new WorkerFileHandler("workers", true);
    workerFileHandler->printUsers();*/
}