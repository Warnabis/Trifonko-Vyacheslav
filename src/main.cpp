#include "Subscription.h"  
#include <iostream>

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

int main() {
    setlocale(LC_ALL, "rus");

    int size = 0;
    auto services = make_unique<Subscription[]>(0);
    Subscription service;
    Subscription* selectedservice = nullptr;
    void saveAllToFile(const unique_ptr<Subscription[]>&services, int size);
    int loadAllFromFile(unique_ptr<Subscription[]>&services);

    int choice;
    do {
        choice = choose();

        switch (choice) {
        case 1:
            service.create(services, size);
            break;
        case 2:
            service.read(services.get(), size);
            break;
        case 3:
            service.update(services.get(), size);
            break;
        case 4:
            service.deletes(services, size);
            break;
        case 5:
            service.workout(services.get(), size, selectedservice);
            break;
        case 6:
            service.compareprices(services.get(), size);
            break;
        case 7:
            saveAllToFile(services, size);
            break;
        case 8:
            size = loadAllFromFile(services);
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
    } while (choice != 6);

    return 0;
}
