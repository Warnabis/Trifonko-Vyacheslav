#ifndef CRUD_H
#define CRUD_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Functions.h"

using namespace std;

template <typename T>
class Crud {
public:
    friend void wait();
    void create(vector<T>& items) const;
    void read(const vector<T>& items) const;
    void update(vector<T>& items) const;
    void deletes(vector<T>& items) const;

};

template <typename T>
void Crud<T>::create(vector<T>& items) const {
    T newitem;
    newitem.input();
    items.push_back(newitem);

    cout << "Объект создан\n";
    wait();
}

template <typename T>
void Crud<T>::read(const vector<T>& items) const {
    if (items.empty()) {
        cout << "Нет объектов для отображения" << endl;
        wait();
        return;
    }

    string checkname;
    cout << "Введите название услуги (или \"all\" для отображения всех): ";
    cin >> checkname;
    cout << endl;

    if (checkname == "all") {
        for (size_t i = 0; i < items.size(); i++) {
            cout << "Объект " << i + 1 << ": ";
            output(items[i]);
            cout << endl;
        }
    }
    else {
        bool found = false;
        for (const auto& item : items) {
            if (item.getname() == checkname) {
                output(item);
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

template <typename T>
void Crud<T>::update(vector<T>& items) const {
    if (items.empty()) {
        cout << "Нет объектов для обновления" << endl;
        return;
    }

    string checkname;
    cout << "Введите название услуги для обновления: ";
    cin >> checkname;

    bool found = false;
    for (auto& item : items) {
        if (item.getname() == checkname) {
            item.input();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Услуга с названием \"" << checkname << "\" не найдена" << endl;
    }
    wait();
}

template <typename T>
void Crud<T>::deletes(vector<T>& items) const {
    if (items.empty()) {
        cout << "Нет объектов для удаления" << endl;
        wait();
        return;
    }

    string checkname;
    cout << "Введите название услуги для удаления (или \"all\" для удаления всех): ";
    cin >> checkname;

    if (checkname == "all") {
        items.clear();
        cout << "Все объекты удалены" << endl;
    }
    else {
        auto it = remove_if(items.begin(), items.end(), [&](const T& item) {
            return item.getname() == checkname;
            });
        if (it != items.end()) {
            items.erase(it, items.end());
            cout << "Услуга \"" << checkname << "\" удалена" << endl;
        }
        else {
            cout << "Услуга с названием \"" << checkname << "\" не найдена" << endl;
        }
    }
    wait();
}


#endif 
