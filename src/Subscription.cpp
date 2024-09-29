#include "Subscription.h"
#include <iostream>
#include <limits>

using namespace std;

void wait() {
    cout << "\nНажмите любую клавишу, чтобы продолжить";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
}

void Subscription::input() {
    cout << "Введите ID услуги: ";
    cin >> id;
    cout << "Введите название услуги: ";
    cin >> name;
    cout << "Введите цену услуги: ";
    cin >> price;
    cout << "Введите кол-во занятий в услуге: ";
    cin >> days;
    cout << endl;
}

void Subscription::output() const {
    cout << "Айди: " << id << " Имя: " << name << " Цена: " << price << " Кол-во занятий в услуге: " << days << endl;
}

void Subscription::create(unique_ptr<Subscription[]>& services, int& size) const {
    auto temp = make_unique<Subscription[]>(size + 1);

    for (int i = 0; i < size; i++) {
        temp[i] = services[i];
    }

    temp[size].input();
    services = move(temp);
    size++;

    cout << "Объект создан\n";
    wait();
}

void Subscription::read(const Subscription* services, int size) const {
    if (size == 0) {
        cout << "Нет объектов для отображения" << endl;
        wait();
        return;
    }

    string checkname;
    cout << "Введите название услуги (или \"all\" для отображения всех): ";
    cin >> checkname;

    if (checkname == "all") {
        for (int i = 0; i < size; i++) {
            cout << "Объект " << i + 1 << ": ";
            services[i].output();
            cout << endl;
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
            cout << "Услуга с названием \"" << checkname << "\" не найдена." << endl;
        }
    }
    wait();
}

void Subscription::update(Subscription* services, int size) const {
    if (size == 0) {
        cout << "Нет объектов для обновления" << endl;
        return;
    }

    string checkname;
    cout << "Введите название услуги для обновления: ";
    cin >> checkname;

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (services[i].name == checkname) {
            services[i].input();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Услуга с названием \"" << checkname << "\" не найдена" << endl;
    }
    wait();
}

void Subscription::deletes(unique_ptr<Subscription[]>& services, int& size) const {
    if (size == 0) {
        cout << "Нет объектов для удаления" << endl;
        wait();
        return;
    }

    string checkname;
    cout << "Введите название услуги для удаления (или \"all\" для удаления всех): ";
    cin >> checkname;

    if (checkname == "all") {
        services.reset();
        size = 0;
        cout << "Все объекты удалены" << endl;
    }
    else {
        bool found = false;
        auto temp = make_unique<Subscription[]>(size - 1);
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
            services = move(temp);
            size--;
            cout << "Услуга \"" << checkname << "\" удалена" << endl;
        }
        else {
            cout << "Услуга с названием \"" << checkname << "\" не найдена" << endl;
        }
    }
    wait();
}

void Subscription::workout(Subscription* services, int size, Subscription*& selectedservice) const {
    if (size == 0) {
        cout << "Нет доступных услуг для выбора" << endl;
        wait();
        return;
    }

    if (selectedservice == nullptr) {
        cout << "Услуга не выбрана. Выберите услугу перед тренировкой" << endl;
        string checkname;
        cout << "Введите название услуги для выбора: ";
        cin >> checkname;

        bool found = false;
        for (int i = 0; i < size; i++) {
            if (services[i].name == checkname) {
                selectedservice = &services[i];
                cout << "Услуга \"" << selectedservice->name << "\" выбрана." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Услуга с названием \"" << checkname << "\" не найдена." << endl;
            wait();
            return;
        }
    }

    int choice;
    do {
        cout << "\n1. Провести тренировку\n2. Проверить статус тренировки\n3. Отменить текущую услугу\n4. Вернуться в главное меню\nВыберите опцию: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный выбор. Попробуйте снова\nВыберите опцию: ";
        }

        switch (choice) {
        case 1:
            if (selectedservice->days > 0) {
                selectedservice->days--;
                cout << "Тренировка проведена. Осталось дней: " << selectedservice->days << endl;
            }
            else {
                cout << "У этой услуги больше не осталось доступных дней для тренировок" << endl;
            }
            wait();
            break;

        case 2:
            cout << "Выбранная услуга: \"" << selectedservice->name << "\"\nОсталось дней: " << selectedservice->days << endl;
            wait();
            break;

        case 3:
            cout << "Выход из услуги \"" << selectedservice->name << "\"." << endl;
            selectedservice = nullptr;
            wait();
            return;

        case 4:
            cout << "Возвращение в главное меню..." << endl;
            wait();
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова" << endl;
            wait();
            break;
        }
    } while (choice != 4);
}

