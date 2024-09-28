#include "Subscription.h" 
#include <iostream>

int choose() {
    int choice;
    std::cout << "\n1. Создать новый объект\n"
        "2. Вывести объект(ы)\n"
        "3. Обновить объект(ы)\n"
        "4. Удалить объект(ы)\n"
        "5. Управление тренировками (выбор, тренировка, статус)\n"
        "6. Выйти из программы\n"
        "Выберите опцию: ";
    std::cin >> choice;
    std::cout << std::endl;
    return choice;
}

int main() {
    setlocale(LC_ALL, "rus");

    int size = 0;
    std::unique_ptr<Subscription[]> services = std::make_unique<Subscription[]>(0);
    Subscription service;
    Subscription* selectedservice = nullptr;

    int choice;
    do {
        choice = choose();

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
            std::cout << "Выход из программы..." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }
    } while (choice != 6);

    return 0;
}
