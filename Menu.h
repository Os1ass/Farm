#pragma once
#include <functional>
#include <Windows.h>
#include "Worker.h"
#include "Accountant.h"
#include "Director.h"
#include "WorkerFileHandler.h"
#include "AccountantFileHandler.h"
#include "DirectorFileHandler.h"

using namespace std;

//Класс опции меню
class MenuOption {
public:
    MenuOption(const string& label, function<void(shared_ptr<FileHandler>)> func);
    string getLabel() const;                        //Получить название опции
    virtual User* execute(shared_ptr<FileHandler>); //Выполнение функции

protected:
    function<void(shared_ptr<FileHandler>)> func_;  //Функция опции меню
    string label_;                                  //Название опции меню
};

class Menu
{
public:
    shared_ptr<FileHandler> fileHandler;    //Обработчик файла

    Menu() : Menu::Menu(false) {}
    Menu(bool isAuthorized) { isAuthorized_ = isAuthorized; }
    Menu(shared_ptr<FileHandler> fileHandler) : Menu::Menu(true) {
        this->fileHandler = fileHandler;
    }

    void addOption(const MenuOption& option);                   //Добавить опцию меню
    void addFileHandler(shared_ptr<FileHandler> fileHandler);   //Добавить обработчик файла
    void run();                                                 //Запуск меню(выбор из опций)

    bool authorize();   //Авторизация пользователя меню

    ~Menu() { options_.clear(); }

private:
    vector<MenuOption> options_;    //Опции меню
    bool isAuthorized_;             //Авторизован ли пользователь меню

};

//Создать меню рабочего
shared_ptr<Menu> createWorkerMenu();

//Создать меню бухгалтера
shared_ptr<Menu> createAccountantMenu();

//Создать меню директора
shared_ptr<Menu> createDirectorMenu();

//Шаблоная функция выбора записи из списка
template<class T>
T* chooseFromList(vector<T*> list)
{
    if (list.size() == 0)
        return nullptr;
    T::printTableHeader();
    int index = 0;
    for (auto element : list)
    {
        element->tablePrint(index);
        index++;
    }
    int choice;
    do
    {
        cout << "\nКакой номер Вас интересует: ";
        choice = readNumber() - 1;
    } while (choice >= list.size());
    return list[choice];
}