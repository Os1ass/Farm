#include "Menu.h"

const string workerFilename = "workers";
const string accountantFilename = "accountants";
const string directorFilename = "directors";

string MenuOption::getLabel() const
{
    return label_;
}

MenuOption::MenuOption(const string& label, function<void(shared_ptr<FileHandler> fileHandler)> func) {
    label_ = label;
    func_ = func;
}

User* MenuOption::execute(shared_ptr<FileHandler> fileHandler) {
    func_(fileHandler);
    return nullptr;
}

void Menu::addFileHandler(shared_ptr<FileHandler> fileHandler)
{
    this->fileHandler = fileHandler;
}

bool Menu::authorize()
{
    string login, password;
    cout << "Введите логин: "; cin >> login;
    cout << "Введите пароль: ";
    password = User::getPassswordFromConsole();
    return isAuthorized_ = fileHandler->authorization(login, password);
}

void Menu::addOption(const MenuOption& option) {
    options_.emplace_back(option);
}

void Menu::run() {
    if (!isAuthorized_) {
        auto authResult = authorize();
        if (!authResult) {
            cout << "Неверный логин или пароль\nПовторите попытку\n";
            system("pause");
            return;
        }
    }

    bool is_exit = false;
    while (!is_exit) {
        system("cls");
        for (int i = 0; i < options_.size(); ++i) {
            cout << i + 1 << ". " << options_[i].getLabel() << endl;
        }

        cout << options_.size() + 1 << ". Выход\n";

        cout << "Введите Ваш выбор: ";
        int choice;
        choice = readNumber();
        if (choice > 0 && choice <= options_.size()) {
            options_[choice - 1].execute(fileHandler);
        }
        else if (choice == options_.size() + 1) {
            is_exit = true;
        }
        else
        {
            cout << "Такой опции нет, попробуйте еще раз\n";
            system("pause");
        }
    }
}

shared_ptr<Menu> createWorkerPrintMenu(shared_ptr<FileHandler> workerFileHandler)
{
    shared_ptr<Menu> workerPrintMenu = make_shared<Menu>(workerFileHandler);
    MenuOption printOption1("Просмотр основной информации", [](shared_ptr<FileHandler> fileHandler) {
        fileHandler->printAuthorizedUser();
        system("pause");
        });
    MenuOption printOption2("Просмотр отработки по дням", [](shared_ptr<FileHandler> fileHandler) {
        static_cast<Worker*>(fileHandler->getAuthorizedUser())->printWorkDays();
        system("pause");
        });

    workerPrintMenu->addOption(printOption1);
    workerPrintMenu->addOption(printOption2);
    return workerPrintMenu;
}

shared_ptr<Menu> createAccountantPrintMenu(shared_ptr<FileHandler> accountantFileHandler)
{
    shared_ptr<Menu> accountantPrintMenu = make_shared<Menu>(accountantFileHandler);
    MenuOption printOption1("Просмотр основной информации", [](shared_ptr<FileHandler> fileHandler) {
        fileHandler->printAuthorizedUser();
        system("pause");
        });
    MenuOption printOption2("Просмотр закупок", [](shared_ptr<FileHandler> fileHandler) {
        static_cast<Accountant*>(fileHandler->getAuthorizedUser())->printPurchases();
        system("pause");
        });
    MenuOption printOption3("Просмотр выплаченных зарплат", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<WorkerFileHandler> workerFileHandler = make_shared<WorkerFileHandler>(workerFilename, true);
        static_cast<Accountant*>(fileHandler->getAuthorizedUser())->printSalaries(workerFileHandler->getWorkersList());
        system("pause");
        });

    accountantPrintMenu->addOption(printOption1);
    accountantPrintMenu->addOption(printOption2);
    accountantPrintMenu->addOption(printOption3);
    return accountantPrintMenu;
}

shared_ptr<Menu> createDirectorPrintMenu(shared_ptr<FileHandler> directorFileHandler)
{
    shared_ptr<Menu> directorPrintMenu = make_shared<Menu>(directorFileHandler);
    MenuOption printOption1("Просмотр основной информации", [](shared_ptr<FileHandler> fileHandler) {
        fileHandler->printAuthorizedUser();
        system("pause");
        });
    MenuOption printOption2("Просмотр отчетов", [](shared_ptr<FileHandler> fileHandler) {
        static_cast<Director*>(fileHandler->getAuthorizedUser())->printReports();
        system("pause");
        });

    directorPrintMenu->addOption(printOption1);
    directorPrintMenu->addOption(printOption2);
    return directorPrintMenu;
}

shared_ptr<Menu> createUserEditMenu(shared_ptr<FileHandler> fileHandler)
{
    shared_ptr<Menu> userEditMenu = make_shared<Menu>(fileHandler);
    MenuOption editOption1("Редактировать логин", [](shared_ptr<FileHandler> fileHandler) {
        string login;
        cout << "Введите новый логин: "; cin >> login;
        fileHandler->editLogin(login);
        });
    MenuOption editOption2("Редактировать пароль", [](shared_ptr<FileHandler> fileHandler) {
        string password = User::readPassword();
        fileHandler->editPassword(password);
        });
    MenuOption editOption3("Редактировать ФИО", [](shared_ptr<FileHandler> fileHandler) {
        string name;
        cout << "Введите новое ФИО: ";
        if (cin.peek() == '\n')
            cin.get();
        getline(cin, name);
        fileHandler->getAuthorizedUser()->setName(name);
        });
    MenuOption editOption4("Редактировать пол", [](shared_ptr<FileHandler> fileHandler) {
        string sex;
        cout << "Введите новый пол: "; cin >> sex;
        fileHandler->getAuthorizedUser()->setSex(sex);
        });
    MenuOption editOption5("Редактировать номер", [](shared_ptr<FileHandler> fileHandler) {
        string phoneNumber;
        cout << "Введите новое номер: "; cin >> phoneNumber;
        fileHandler->getAuthorizedUser()->setPhoneNumber(phoneNumber);
        });
    MenuOption editOption6("Редактировать дату рождения", [](shared_ptr<FileHandler> fileHandler) {
        Date birthDate;
        birthDate.initByConsole();
        fileHandler->getAuthorizedUser()->setBirthDate(birthDate);
        });

    userEditMenu->addOption(editOption1);
    userEditMenu->addOption(editOption2);
    userEditMenu->addOption(editOption3);
    userEditMenu->addOption(editOption4);
    userEditMenu->addOption(editOption5);
    userEditMenu->addOption(editOption6);
    return userEditMenu;
}

shared_ptr<Menu> createWorkerEditMenu(shared_ptr<FileHandler> workerFileHandler)
{
    return createUserEditMenu(workerFileHandler);
}

shared_ptr<Menu> createAccountantEditMenu(shared_ptr<FileHandler> accountantFileHandler)
{
    return createUserEditMenu(accountantFileHandler);
}

shared_ptr<Menu> createDirectorEditMenu(shared_ptr<FileHandler> directorFileHandler)
{
    return createUserEditMenu(directorFileHandler);
}

shared_ptr<Menu> createWorkersManagmentMenu(shared_ptr<FileHandler> directorFileHandler)
{
    shared_ptr<Menu> workersManagmentMenu = make_shared<Menu>(directorFileHandler);
    MenuOption managmentOption1("Просмотр рабочих", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<WorkerFileHandler> workerFileHandler = make_shared<WorkerFileHandler>(workerFilename, true);
        cout << "Нажмите\n1 - Посмотреть всех рабочих\n2 - посмотреть конкретного рабочего\n";
        cout << "Введите Ваш выбор: "; 
        int choice = readNumber();
        if (choice != 1 && choice != 2)
        {
            cout << "Такой опции нет\n";
            system("pause");
            return;
        }
        if (choice == 2)
        {
            Worker* worker = chooseFromList(workerFileHandler->getWorkersList());
            if (!worker)
            {
                cout << "Такого рабочего нет\n";
                system("pause");
                return;
            }
            system("cls");
            workerFileHandler->setAuthorizedUserId(worker->getId());
            shared_ptr<Menu> workerPrintMenu = createWorkerPrintMenu(workerFileHandler);
            workerPrintMenu->run();
            return;
        }
        workerFileHandler->printUsers();
        system("pause");
        });
    MenuOption managmentOption2("Уволить рабочего", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<WorkerFileHandler> workerFileHandler = make_shared<WorkerFileHandler>(workerFilename, true);
        Worker* worker = chooseFromList(workerFileHandler->getWorkersList());
        if (!worker)
        {
            cout << "Такого рабочего нет\n";
            system("pause");
            return;
        }
        workerFileHandler->removeUser(worker->getId());
        system("pause");
        });
    MenuOption managmentOption3("Добавить рабочего", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<WorkerFileHandler> workerFileHandler = make_shared<WorkerFileHandler>(workerFilename, true);
        Worker* worker = new Worker();
        worker->registration();
        workerFileHandler->addUser(worker);
        system("pause");
        });

    workersManagmentMenu->addOption(managmentOption1);
    workersManagmentMenu->addOption(managmentOption2);
    workersManagmentMenu->addOption(managmentOption3);
    return workersManagmentMenu;
}

shared_ptr<Menu> createAccountantsManagmentMenu(shared_ptr<FileHandler> directorFileHandler)
{
    shared_ptr<Menu> accountantsManagmentMenu = make_shared<Menu>(directorFileHandler);
    MenuOption managmentOption1("Просмотр бухгалтеров", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<AccountantFileHandler> accountantFileHandler = make_shared<AccountantFileHandler>(accountantFilename, true);
        cout << "Нажмите\n1 - Посмотреть всех бухгалтеров\n2 - посмотреть конкретного бухгалтера\n";
        cout << "Введите Ваш выбор: ";
        int choice = readNumber();
        if (choice != 1 && choice != 2)
        {
            cout << "Такой опции нет\n";
            system("pause");
            return;
        }
        if (choice == 2)
        {
            Accountant* accountant = chooseFromList(accountantFileHandler->getAccountantsList());
            if (!accountant)
            {
                cout << "Такого бухгалтера нет\n";
                system("pause");
                return;
            }
            system("cls");
            accountantFileHandler->setAuthorizedUserId(accountant->getId());
            shared_ptr<Menu> accountantPrintMenu = createAccountantPrintMenu(accountantFileHandler);
            accountantPrintMenu->run();
            return;
        }
        accountantFileHandler->printUsers();
        system("pause");
        });
    MenuOption managmentOption2("Уволить бухглатера", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<AccountantFileHandler> accountantFileHandler = make_shared<AccountantFileHandler>(accountantFilename, true);
        Accountant* accountant = chooseFromList(accountantFileHandler->getAccountantsList());
        if (!accountant)
        {
            cout << "Такого бухгалтера нет\n";
            system("pause");
            return;
        }
        accountantFileHandler->removeUser(accountant->getId());
        system("pause");
        });
    MenuOption managmentOption3("Добавить бухглатера", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<AccountantFileHandler> accountantFileHandler = make_shared<AccountantFileHandler>(accountantFilename, true);
        Accountant* accountant = new Accountant();
        accountant->registration();
        accountantFileHandler->addUser(accountant);
        system("pause");
        });

    accountantsManagmentMenu->addOption(managmentOption1);
    accountantsManagmentMenu->addOption(managmentOption2);
    accountantsManagmentMenu->addOption(managmentOption3);
    return accountantsManagmentMenu;
}

shared_ptr<Menu> createStaffMenu(shared_ptr<FileHandler> directorFileHandler)
{
    shared_ptr<Menu> staffMenu = make_shared<Menu>(directorFileHandler);
    MenuOption staffOption1("Управление рабочими", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> workersManagmentMenu = createWorkersManagmentMenu(fileHandler);
        workersManagmentMenu->run();
        });
    MenuOption staffOption2("Управление бухгалтерами", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> accountantsManagmentMenu = createAccountantsManagmentMenu(fileHandler);
        accountantsManagmentMenu->run();
        });

    staffMenu->addOption(staffOption1);
    staffMenu->addOption(staffOption2);
    return staffMenu;
}

shared_ptr<Menu> createWorkerMenu()
{
    shared_ptr<Menu> workerMenu = make_shared<Menu>();
    workerMenu->fileHandler = make_shared<WorkerFileHandler>(workerFilename);
    MenuOption workerOption1("Просмотр своей учетной записи", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> workerPrintMenu = createWorkerPrintMenu(fileHandler);
        workerPrintMenu->run();
        });
    MenuOption workerOption2("Редактирование своей учетной записи", [&](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> workerEditMenu = createWorkerEditMenu(fileHandler);
        workerEditMenu->run();
        });
    MenuOption workerOption3("Добавить информацию об отработке", [](shared_ptr<FileHandler> fileHandler) {
        cout << "Введите дату или нажмите (отработка на текущий день)\n";
        Date date;
        date.readDate();
        int amount;
        Worker* worker = static_cast<Worker*>(fileHandler->getAuthorizedUser());
        cout << worker->getWorkString();
        cin >> amount;
        worker->doWork(date, amount);
        system("pause");
        });

    workerMenu->addOption(workerOption1);
    workerMenu->addOption(workerOption2);
    workerMenu->addOption(workerOption3);
    return workerMenu;
}

shared_ptr<Menu> createAccountantMenu()
{
    shared_ptr<Menu> accountantMenu = make_shared<Menu>();
    accountantMenu->fileHandler = make_shared<AccountantFileHandler>(accountantFilename);
    MenuOption accountantOption1("Просмотр своей учетной записи", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> accountantPrintMenu = createAccountantPrintMenu(fileHandler);
        accountantPrintMenu->run();
        });
    MenuOption accountantOption2("Редактирование своей учетной записи", [&](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> accountantEditMenu = createAccountantEditMenu(fileHandler);
        accountantEditMenu->run();
        });
    MenuOption accountantOption3("Просмотреть список рабочих", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<WorkerFileHandler> workerFileHandler = make_shared<WorkerFileHandler>(workerFilename, true);
        workerFileHandler->printUsers();
        system("pause");
        });
    MenuOption accountantOption4("Выплатить зарплату", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<WorkerFileHandler> workerFileHandler = make_shared<WorkerFileHandler>(workerFilename, true);
        Worker* worker = chooseFromList(workerFileHandler->getWorkersList());
        if (!worker)
        {
            cout << "Такого рабочего нет\n";
            system("pause");
            return;
        }
        system("cls");
        int choice, size = worker->getNumberUnpaidWorkDays();
        if (size == 0)
        {
            cout << "\n Неоплаченных отработок нет\n";
            system("pause");
            return;
        }
        worker->printUnpaidWorkDays();
        cout << "\nВведите день, за который хотите выплатить зарплату: "; 
        choice = readNumber();
        if (--choice >= size || choice < 0)
        {
            cout << "Ошибка, такого дня нет\n";
            system("pause");
            return;
        }
        int salary;
        cout << "Введите зарплату за рабочий день: "; cin >> salary;
        Date workDayDate = worker->getUnpaidWorkDayDate(choice);
        worker->setSalaryByDate(workDayDate, salary);
        static_cast<Accountant*>(fileHandler->getAuthorizedUser())->addSalary(workDayDate, worker->getId(), salary);
        system("pause");
        });
    MenuOption accountantOption5("Совершить закупку", [](shared_ptr<FileHandler> fileHandler) {
        Purchase* newPurchase = new Purchase();
        newPurchase->initByConsole();
        static_cast<Accountant*>(fileHandler->getAuthorizedUser())->addPurchase(newPurchase);
        system("pause");
        });

    accountantMenu->addOption(accountantOption1);
    accountantMenu->addOption(accountantOption2);
    accountantMenu->addOption(accountantOption3);
    accountantMenu->addOption(accountantOption4);
    accountantMenu->addOption(accountantOption5);
    return accountantMenu;
}

shared_ptr<Menu> createDirectorMenu()
{
    shared_ptr<Menu> directorMenu = make_shared<Menu>();
    directorMenu->fileHandler = make_shared<DirectorFileHandler>(directorFilename);
    MenuOption directorOption1("Просмотр своей учетной записи", [](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> directorPrintMenu = createDirectorPrintMenu(fileHandler);
        directorPrintMenu->run();
        });
    MenuOption directorOption2("Редактирование своей учетной записи", [&](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> directorEditMenu = createDirectorEditMenu(fileHandler);
        directorEditMenu->run();
        });
    MenuOption directorOption3("Получить отчет", [&](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<WorkerFileHandler> workerFileHandler = make_shared<WorkerFileHandler>(workerFilename, true);
        shared_ptr<AccountantFileHandler> accountantFileHandler = make_shared<AccountantFileHandler>(accountantFilename, true);
        static_cast<Director*>(fileHandler->getAuthorizedUser())->getReport(accountantFileHandler->getAccountantsList(), workerFileHandler->getWorkersList());
        system("pause");
        });
    MenuOption directorOption4("Управление персоналом", [&](shared_ptr<FileHandler> fileHandler) {
        shared_ptr<Menu> staffMenu = createStaffMenu(fileHandler);
        staffMenu->run();
        });

    directorMenu->addOption(directorOption1);
    directorMenu->addOption(directorOption2);
    directorMenu->addOption(directorOption3);
    directorMenu->addOption(directorOption4);
    return directorMenu;
}