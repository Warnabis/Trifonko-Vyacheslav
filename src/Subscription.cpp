#include "Subscription.h"
#include <iostream>
#include <limits>

using namespace std;

void Subscription::saveSubscriptionsToFile(ofstream& ofs) const {
    ofs << id << endl;
    ofs << name << endl;
    ofs << price << endl;
    ofs << days << endl;
}

void Subscription::loadSubscriptionsFromFile(ifstream& ifs) {
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
    cout << endl << service;

}

void Subscription::create(vector<Subscription>& services) const {
    Subscription newservice;
    newservice.input();
    services.push_back(newservice);

    cout << "Объект создан\n";
    wait();
}

void Subscription::read(const vector<Subscription>& services) const {
    if (services.empty()) {
        cout << "Нет объектов для отображения" << endl;
        wait();
        return;
    }

    string checkname;
    cout << "Введите название услуги (или \"all\" для отображения всех): ";
    cin >> checkname;
    cout << endl;

    if (checkname == "all") {
        for (size_t i = 0; i < services.size(); i++) {
            cout << "Объект " << i + 1 << ": ";
            output(services[i]);
            cout << endl;
        }
    }
    else {
        bool found = false;
        for (const auto& service : services) {
            if (service.name == checkname) {
                output(service);
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

void Subscription::update(vector<Subscription>& services) const {
    if (services.empty()) {
        cout << "Нет объектов для обновления" << endl;
        return;
    }

    string checkname;
    cout << "Введите название услуги для обновления: ";
    cin >> checkname;

    bool found = false;
    for (auto& service : services) {
        if (service.name == checkname) {
            service.input();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Услуга с названием \"" << checkname << "\" не найдена" << endl;
    }
    wait();
}

void Subscription::deletes(vector<Subscription>& services) const {
    if (services.empty()) {
        cout << "Нет объектов для удаления" << endl;
        wait();
        return;
    }

    string checkname;
    cout << "Введите название услуги для удаления (или \"all\" для удаления всех): ";
    cin >> checkname;

    if (checkname == "all") {
        services.clear();
        cout << "Все объекты удалены" << endl;
    }
    else {
        auto it = remove_if(services.begin(), services.end(), [&](const Subscription& service) {
            return service.name == checkname;
            });
        if (it != services.end()) {
            services.erase(it, services.end());
            cout << "Услуга \"" << checkname << "\" удалена" << endl;
        }
        else {
            cout << "Услуга с названием \"" << checkname << "\" не найдена" << endl;
        }
    }
    wait();
}

void Subscription::comparePrices(const vector<Subscription>& services) const {
    if (services.size() < 2) {
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

    for (const auto& service : services) {
        if (service.name == checkname1) {
            service1 = &service;
        }
        else if (service.name == checkname2) {
            service2 = &service;
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
            cout << "Услуга \"" << checkname2 << "\" дороже услуги \"" << checkname1 << "\"." << endl;
        }       
    }
    else {
        if (!service1) {
            cout << "Услуга с названием \"" << checkname1 << "\" не найдена." << endl;
        }
        if (!service2) {
            cout << "Услуга с названием \"" << checkname2 << "\" не найдена." << endl;
        }
    }
    wait();
}

void saveAllSubscriptionsToFile(const vector<Subscription>& subscriptions) {
    ofstream ofs("subscriptions.txt");
    if (!ofs) {
        cout << "Ошибка открытия файла для записи!\n";
        return;
    }

    for (const auto& sub : subscriptions) {
        sub.saveSubscriptionsToFile(ofs);
    }

    ofs.close();
    cout << "Данные о подписках успешно сохранены в файл.\n";
}

void loadAllSubscriptionsFromFile(vector<Subscription>& subscriptions) {
    ifstream ifs("subscriptions.txt");
    if (!ifs) {
        cout << "Ошибка открытия файла для чтения!\n";
        return;
    }

    subscriptions.clear();

    while (true) {
        Subscription tempSub;
        tempSub.loadSubscriptionsFromFile(ifs);
        if (ifs.eof()) {
            break;
        }
        subscriptions.push_back(tempSub);
    }

    ifs.close();
    cout << "Данные о подписках загружены из файла.\n";
}