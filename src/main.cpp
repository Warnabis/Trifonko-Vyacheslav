#include "Subscription.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "rus");
    Subscription service;
    Subscription* services = nullptr;
    int size = 0;
    Subscription* selectedservice = nullptr;

    int choice;
    do {
        std::cout << "Меню:\n"
            << "1. Создать услугу\n"
            << "2. Показать услуги\n"
            << "3. Обновить услугу\n"
            << "4. Удалить услугу\n"
            << "5. Тренировка\n"
            << "6. Выход\n"
            << "Выберите опцию: ";

        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный выбор. Попробуйте снова\nВыберите опцию: ";
        }

        choose(choice, service, services, size, selectedservice);
    } while (choice != 6);

    delete[] services; 
    return 0;
}
