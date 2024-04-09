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

//����� ����� ����
class MenuOption {
public:
    MenuOption(const string& label, function<void(shared_ptr<FileHandler>)> func);
    string getLabel() const;                        //�������� �������� �����
    virtual User* execute(shared_ptr<FileHandler>); //���������� �������

protected:
    function<void(shared_ptr<FileHandler>)> func_;  //������� ����� ����
    string label_;                                  //�������� ����� ����
};

class Menu
{
public:
    shared_ptr<FileHandler> fileHandler;    //���������� �����

    Menu() : Menu::Menu(false) {}
    Menu(bool isAuthorized) { isAuthorized_ = isAuthorized; }
    Menu(shared_ptr<FileHandler> fileHandler) : Menu::Menu(true) {
        this->fileHandler = fileHandler;
    }

    void addOption(const MenuOption& option);                   //�������� ����� ����
    void addFileHandler(shared_ptr<FileHandler> fileHandler);   //�������� ���������� �����
    void run();                                                 //������ ����(����� �� �����)

    bool authorize();   //����������� ������������ ����

    ~Menu() { options_.clear(); }

private:
    vector<MenuOption> options_;    //����� ����
    bool isAuthorized_;             //����������� �� ������������ ����

};

//������� ���� ��������
shared_ptr<Menu> createWorkerMenu();

//������� ���� ����������
shared_ptr<Menu> createAccountantMenu();

//������� ���� ���������
shared_ptr<Menu> createDirectorMenu();

//�������� ������� ������ ������ �� ������
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
        cout << "\n����� ����� ��� ����������: ";
        choice = readNumber() - 1;
    } while (choice >= list.size());
    return list[choice];
}