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

void Subscription::saveToFile(ofstream& ofs) const {
    ofs << id << endl;
    ofs << name << endl;
    ofs << price << endl;
    ofs << days << endl;
}

void Subscription::loadFromFile(ifstream& ifs) {
    ifs >> id;
    ifs.ignore(); 
    getline(ifs, name);
    ifs >> price;
    ifs >> days;
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

void output(const Subscription& service) {
    cout << "Айди: " << service.id << " Имя: " << service.name << " Цена: " << service.price << " Кол-во занятий в услуге: " << service.days << endl;
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
            output(services[i]);
            cout << endl;
        }
    }
    else {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (services[i].name == checkname) {
                output(services[i]);
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

bool operator==(const Subscription& lhs, const Subscription& rhs) {
    return lhs.price == rhs.price; 
}

bool operator>(const Subscription& lhs, const Subscription& rhs) {
    return lhs.price > rhs.price; 
}

ostream& operator<<(ostream& os, const Subscription& service) {
    os << "Айди: " << service.id << ", Имя: " << service.name
        << ", Цена: " << service.price << ", Кол-во занятий: " << service.days;
    return os;
}

void Subscription::compareprices(const Subscription* services, int size) const {
    if (size < 2) {
        cout << "Для сравнения цен нужно минимум две услуги." << endl;
        wait();
        return;

    }

    string checkname1;
    string checkname2;
    cout << "Введите название первой услуги: ";
    cin >> checkname1;
    cout << "Введите название второй услуги: ";
    cin >> checkname2;

    const Subscription* service1 = nullptr;
    const Subscription* service2 = nullptr;

    for (int i = 0; i < size; i++) {
        if (services[i].name == checkname1) {
            service1 = &services[i];
        }
        else if (services[i].name == checkname2) {
            service2 = &services[i];
        }
    }

    if (service1 && service2) {
        if (*service1 == *service2) {
            cout << "Услуги \"" << checkname1 << "\" и \"" << checkname2 << "\" имеют одинаковую цену." << endl;
        }
        else if (*service1 > *service2) {
            cout << "Услуга \"" << checkname1 << "\" дороже услуги \"" << checkname2 << "\"." << endl;
        }
        else {
            cout << "Услуга \"" << checkname1 << "\" дешевле услуги \"" << checkname2 << "\"." << endl;
        }
    }
    else {
        cout << "Одна или обе услуги не найдены." << endl;
    }
    wait();
}

void saveAllToFile(const Subscription* services, int size) {
    ofstream ofs("subscriptions.txt");
    if (!ofs) {
        cout << "Ошибка открытия файла для записи!" << endl;
        wait();
        return;
    }

    for (int i = 0; i < size; ++i) {
        services[i].saveToFile(ofs);
    }
    ofs.close();
    cout << "Услуги сохранены в файл subscriptions.txt." << endl;
    wait();
}

int loadAllFromFile(unique_ptr<Subscription[]>& services) {
    ifstream ifs("subscriptions.txt");
    if (!ifs) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return 0;
    }

    int size = 0;
    while (true) {
        auto temp = make_unique<Subscription[]>(size + 1);
        if (size > 0) {
            for (int i = 0; i < size; i++) {
                temp[i] = services[i];
            }
        }

        temp[size].loadFromFile(ifs);

        
        if (ifs.eof() || ifs.fail()) {
            if (ifs.fail()) {
                cout << "Ошибка чтения данных из файла." << endl;
            }
            break; 
        }

        services = move(temp);
        size++;
    }

    ifs.close();
    cout << "Услуги загружены из файла subscriptions.txt." << endl;
    wait();
    return size;
}
