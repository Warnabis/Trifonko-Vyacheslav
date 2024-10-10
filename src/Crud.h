#ifndef CRUD_H
#define CRUD_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Functions.h"

template <typename T>
class Crud {
public:
    friend void wait();
    void create(std::vector<T>& items) const;
    void read(const std::vector<T>& items) const;
    void update(std::vector<T>& items) const;
    void deletes(std::vector<T>& items) const;
};

template <typename T>
void Crud<T>::create(std::vector<T>& items) const {
    T newitem;
    newitem.input();
    items.push_back(newitem);

    std::cout << "Объект создан\n";
    wait();
}

template <typename T>
void Crud<T>::read(const std::vector<T>& items) const {
    if (items.empty()) {
        std::cout << "Нет объектов для отображения" << std::endl;
        wait();
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги (или \"all\" для отображения всех): ";
    std::cin >> checkname;
    std::cout << std::endl;

    if (checkname == "all") {
        for (size_t i = 0; i < items.size(); i++) {
            std::cout << "Объект " << i + 1 << ": ";
            output(items[i]);
            std::cout << std::endl;
        }
    } else {
        bool found = false;
        for (const auto& item : items) {
            if (item.getname() == checkname) {
                output(item);
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

template <typename T>
void Crud<T>::update(std::vector<T>& items) const {
    if (items.empty()) {
        std::cout << "Нет объектов для обновления" << std::endl;
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги для обновления: ";
    std::cin >> checkname;

    bool found = false;
    for (auto& item : items) {
        if (item.getname() == checkname) {
            item.input();
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Услуга с названием \"" << checkname << "\" не найдена" << std::endl;
    }
    wait();
}

template <typename T>
void Crud<T>::deletes(std::vector<T>& items) const {
    if (items.empty()) {
        std::cout << "Нет объектов для удаления" << std::endl;
        wait();
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги для удаления (или \"all\" для удаления всех): ";
    std::cin >> checkname;

    if (checkname == "all") {
        items.clear();
        std::cout << "Все объекты удалены" << std::endl;
    } else {
        auto it = std::remove_if(items.begin(), items.end(), [&](const T& item) {
            return item.getname() == checkname;
        });
        if (it != items.end()) {
            items.erase(it, items.end());
            std::cout << "Услуга \"" << checkname << "\" удалена" << std::endl;
        } else {
            std::cout << "Услуга с названием \"" << checkname << "\" не найдена" << std::endl;
        }
    }
    wait();
}

#endif
