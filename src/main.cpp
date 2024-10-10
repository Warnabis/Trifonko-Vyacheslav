#include "Subscription.h"
#include "Crud.h"
#include "Activation.h"
#include "Functions.h"
#include <iostream>
#include <vector>

using namespace std;

int choose() {
    int choice;
    cout << "\n1. Создать новый объект\n"
        "2. Вывести объект(ы)\n"
        "3. Обновить объект(ы)\n"
        "4. Удалить объект(ы)\n"
        "5. Управление тренировками (выбор, тренировка, статус)\n"
        "6. Сравнить цены двух услуг\n"
        "7. Сохранить все услуги в файл\n"
        "8. Загрузить услуги из файла\n"
        "9. Выйти из программы\n"
        "Выберите опцию: ";
    cin >> choice;
    cout << endl;
    return choice;
}

void savealltofile(const vector<Subscription>& services);
size_t loadallfromfile(vector<Subscription>& services);

int main() {
    setlocale(LC_ALL, "rus");

    vector<Subscription> services;

    Subscription service;
    Subscription* selectedservice = nullptr;

    int choice;
    do {
        choice = choose();

        switch (choice) {
        case 1:
            service.create(services);
            break;
        case 2:
            service.read(services);
            break;
        case 3:
            service.update(services);
            break;
        case 4:
            service.deletes(services);
            break;
        case 5:
            service.workout(services, selectedservice);
            break;
        case 6:
            service.compareprices(services);
            break;
        case 7:
            savealltofile(services);
            break;
        case 8:
            loadallfromfile(services);
            break;
        case 9:
            cout << "Выход из программы..." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}