#include "Subscription.h"
#include <iostream>
#include <memory>

using namespace std;

int chooseOption() {
    int choice;
    cout << "\n1. Создать новый объект\n2. Вывести объект(ы)\n3. Обновить объект(ы)\n4. Удалить объект(ы)\n5. Управление тренировками (выбор, тренировка, статус)\n6. Выйти из программы\nВыберите опцию: ";
    cin >> choice;
    cout << endl;
    return choice;
}

int main() {
    setlocale(LC_ALL, "rus");

    int size = 0;
    unique_ptr<Subscription[]> services(new Subscription[0]);
    Subscription service;
    Subscription* selectedservice = nullptr;

    int choice;
    do {
        choice = chooseOption();

        switch (choice) {
        case 1:
            service.create(services, size);
            break;
        case 2:
            service.read(services, size);
            break;
        case 3:
            service.update(services, size);
            break;
        case 4:
            service.deletes(services, size);
            break;
        case 5:
            service.workout(services, size, selectedservice);
            break;
        case 6:
            cout << "Выход из программы..." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова" << endl;
            break;
        }
    } while (choice != 6);

    return 0;
}
