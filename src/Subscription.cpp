#include "Subscription.h"
#include <iostream>
#include <limits>


void wait() {
    std::cout << "\nНажмите любую клавишу, чтобы продолжить";
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("cls");
}

void Subscription::input() {
    std::cout << "Введите ID услуги: ";
    std::cin >> id;
    std::cout << "Введите название услуги: ";
    std::cin >> name;
    std::cout << "Введите цену услуги: ";
    std::cin >> price;
    std::cout << "Введите кол-во занятий в услуге: ";
    std::cin >> days;
    std::cout << std::endl;
}

void Subscription::output() const {
    std::cout << "Айди: " << id << " Имя: " << name << " Цена: " << price << " Кол-во занятий в услуге: " << days << std::endl;
}

void Subscription::create(std::unique_ptr<Subscription[]>& services, int& size) const {
    auto temp = std::make_unique<Subscription[]>(size + 1);

    for (int i = 0; i < size; i++) {
        temp[i] = services[i];
    }

    temp[size].input();
    services = std::move(temp);
    size++;

    std::cout << "Объект создан\n";
    wait();
}

void Subscription::read(Subscription* services, int size) const {
    if (size == 0) {
        std::cout << "Нет объектов для отображения" << std::endl;
        wait();
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги (или \"all\" для отображения всех): ";
    std::cin >> checkname;

    if (checkname == "all") {
        for (int i = 0; i < size; i++) {
            std::cout << "Объект " << i + 1 << ": ";
            services[i].output();
            std::cout << std::endl;
        }
    }
    else {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (services[i].name == checkname) {
                services[i].output();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Услуга с названием \"" << checkname << "\" не найдена." << std::endl;
        }
    }
    wait();
}

void Subscription::update(std::unique_ptr<Subscription[]>& services, int size) const {
    if (size == 0) {
        std::cout << "Нет объектов для обновления" << std::endl;
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги для обновления: ";
    std::cin >> checkname;

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (services[i].name == checkname) {
            services[i].input();
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Услуга с названием \"" << checkname << "\" не найдена" << std::endl;
    }
    wait();
}

void Subscription::deletes(std::unique_ptr<Subscription[]>& services, int& size) const {
    if (size == 0) {
        std::cout << "Нет объектов для удаления" << std::endl;
        wait();
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги для удаления (или \"all\" для удаления всех): ";
    std::cin >> checkname;

    if (checkname == "all") {
        services.reset();
        size = 0;
        std::cout << "Все объекты удалены" << std::endl;
    }
    else {
        bool found = false;
        auto temp = std::make_unique<Subscription[]>(size - 1);
        int index = 0;

        for (int i = 0; i < size; i++) {
            if (services[i].name != checkname) {
                index++;
                temp[index] = services[i];
            }
            else {
                found = true;
            }
        }

        if (found) {
            services = std::move(temp);
            size--;
            std::cout << "Услуга \"" << checkname << "\" удалена" << std::endl;
        }
        else {
            std::cout << "Услуга с названием \"" << checkname << "\" не найдена" << std::endl;
        }
    }
    wait();
}

void Subscription::workout(const std::unique_ptr<Subscription[]>& services, int size, Subscription*& selectedservice) const {
    if (size == 0) {
        std::cout << "Нет доступных услуг для выбора" << std::endl;
        wait();
        return;
    }

    if (selectedservice == nullptr) {
        std::cout << "Услуга не выбрана. Выберите услугу перед тренировкой" << std::endl;
        std::string checkname;
        std::cout << "Введите название услуги для выбора: ";
        std::cin >> checkname;

        bool found = false;
        for (int i = 0; i < size; i++) {
            if (services[i].name == checkname) {
                selectedservice = &services[i];
                std::cout << "Услуга \"" << selectedservice->name << "\" выбрана." << std::endl;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Услуга с названием \"" << checkname << "\" не найдена." << std::endl;
            wait();
            return;
        }
    }

    int choice;
    do {
        std::cout << "\n1. Провести тренировку\n2. Проверить статус тренировки\n3. Отменить текущую услугу\n4. Вернуться в главное меню\nВыберите опцию: ";
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный выбор. Попробуйте снова\nВыберите опцию: ";
        }

        switch (choice) {
        case 1:
            if (selectedservice->days > 0) {
                selectedservice->days--;
                std::cout << "Тренировка проведена. Осталось дней: " << selectedservice->days << std::endl;
            }
            else {
                std::cout << "У этой услуги больше не осталось доступных дней для тренировок" << std::endl;
            }
            wait();
            break;

        case 2:
            std::cout << "Выбранная услуга: \"" << selectedservice->name << "\"\nОсталось дней: " << selectedservice->days << std::endl;
            wait();
            break;

        case 3:
            std::cout << "Выход из услуги \"" << selectedservice->name << "\"." << std::endl;
            selectedservice = nullptr;
            wait();
            return;

        case 4:
            std::cout << "Возвращение в главное меню..." << std::endl;
            wait();
            break;

        default:
            std::cout << "Неверный выбор. Попробуйте снова" << std::endl;
            wait();
            break;
        }
    } while (choice != 4);
}
