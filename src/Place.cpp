#include "Place.h"
#include "Subscription.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void Place::savePlacesToFile(ofstream& ofs) const {
    ofs << name << endl;
    ofs << address << endl;
    ofs << hours << endl;
    ofs << activated << endl;
    ofs << subscriptions.size() << endl; // Количество подписок
    for (const auto& subscription : subscriptions) {
        ofs << subscription.getName() << endl; // Получаем имя подписки
    }
}


void Place::loadPlacesFromFile(ifstream& ifs, const std::vector<Subscription>& existingSubscriptions) {
    getline(ifs, name);
    getline(ifs, address);
    getline(ifs, hours);
    ifs >> activated;
    size_t subCount;
    ifs >> subCount;
    ifs.ignore(); // Игнорируем символ новой строки
    subscriptions.clear();

    for (size_t i = 0; i < subCount; i++) {
        string subscriptionName;
        getline(ifs, subscriptionName);

        // Находим существующую подписку по имени
        auto it = std::find_if(existingSubscriptions.begin(), existingSubscriptions.end(),
            [&subscriptionName](const Subscription& sub) {
                return sub.getName() == subscriptionName;
            });

        if (it != existingSubscriptions.end()) {
            // Добавляем найденную подписку в вектор subscriptions
            subscriptions.push_back(*it);
        }
        else {
            cout << "Подписка с именем " << subscriptionName << " не найдена.\n";
            return;
        }
    }
}

void Place::create(std::vector<Place>& places, const std::vector<Subscription>& subscriptions) const {

    Place newPlace;
    std::cout << "Введите название зала: ";
    std::cin >> newPlace.name;  // Вводим название зала

    std::cout << "Введите адрес зала: ";
    std::cin >> newPlace.address;  // Вводим адрес зала

    std::cout << "Введите время работы (формат HH:MM-HH:MM): ";
    std::cin >> newPlace.hours;  // Вводим время работы

    std::cout << "Зал активен? (1 - да, 0 - нет): ";
    std::cin >> newPlace.activated;
    cin.ignore();

    // Выбор подписок
    std::vector<Subscription> selectedSubscriptions;
    std::string subscriptionName;

    while (true) {
        std::cout << "Введите название подписки (или 'end' для завершения): ";
        std::getline(std::cin, subscriptionName);

        if (subscriptionName == "end") {
            break; // Завершение ввода подписок
        }

        // Проверяем, существует ли подписка с таким именем
        auto subIt = std::find_if(subscriptions.begin(), subscriptions.end(),
            [&subscriptionName](const Subscription& sub) { return sub.getName() == subscriptionName; });
        if (subIt != subscriptions.end()) {
            // Если подписка найдена, добавляем ее в вектор выбранных подписок
            selectedSubscriptions.push_back(*subIt);
        }
        else {
            std::cout << "Подписка с именем '" << subscriptionName << "' не найдена!\n";
        }
        cout << "Объект создан\n";
    }

   
    // Добавляем подписки в зал
    newPlace.subscriptions = selectedSubscriptions; // Предполагается, что у вас есть доступ к полю subscriptions
    places.push_back(newPlace); // Добавляем новый зал в вектор
}


void Place::read(const vector<Place>& places) const {
    if (places.empty()) {
        cout << "Нет объектов для отображения." << endl;
        return;
    }

    for (size_t i = 0; i < places.size(); i++) {
        cout << "Объект " << i + 1 << ":\n" << places[i] << endl;
    }
}

void Place::update(vector<Place>& places, const vector<Subscription>& availableSubscriptions) const {
    if (places.empty()) {
        cout << "Нет объектов для обновления." << endl;
        return;
    }

    int index;
    cout << "Введите номер зала для обновления: ";
    cin >> index;

    if (index <= 0 || index > places.size()) {
        cout << "Неверный номер зала." << endl;
        return;
    }

    Place& placeToUpdate = places[index - 1];

    string name, address, hours;
    cout << "Введите новое название зала (оставьте пустым для сохранения старого): ";
    cin.ignore();
    getline(cin, name);
    cout << "Введите новый адрес зала (оставьте пустым для сохранения старого): ";
    getline(cin, address);
    cout << "Введите новые часы работы (оставьте пустым для сохранения старых): ";
    getline(cin, hours);

    if (!name.empty()) placeToUpdate.setName(name);
    if (!address.empty()) placeToUpdate.setAddress(address);
    if (!hours.empty()) placeToUpdate.setHours(hours);

    // Обновление подписок
    int numSubscriptions;
    cout << "Сколько подписок вы хотите добавить? ";
    cin >> numSubscriptions;
    for (int i = 0; i < numSubscriptions; i++) {
        cout << "Доступные подписки:\n";
        for (size_t j = 0; j < availableSubscriptions.size(); j++) {
            cout << j + 1 << ". " << availableSubscriptions[j].getName() << "\n";
        }
        int subIndex;
        cout << "Выберите подписку по номеру: ";
        cin >> subIndex;
        if (subIndex > 0 && subIndex <= availableSubscriptions.size()) {
            placeToUpdate.addSubscription(availableSubscriptions[subIndex - 1]);
        }
        else {
            cout << "Неверный номер подписки." << endl;
        }
    }

    cout << "Зал обновлён успешно.\n";
}

void Place::deletes(vector<Place>& places) const {
    if (places.empty()) {
        cout << "Нет объектов для удаления." << endl;
        return;
    }

    int index;
    cout << "Введите номер зала для удаления: ";
    cin >> index;

    if (index <= 0 || index > places.size()) {
        cout << "Неверный номер зала." << endl;
        return;
    }

    places.erase(places.begin() + (index - 1));
    cout << "Зал удалён успешно.\n";
}

void saveAllPlacesToFile(const vector<Place>& places) {
    ofstream ofs("places.txt");
    if (!ofs) {
        cout << "Ошибка открытия файла для записи!\n";
        return;
    }

    for (const auto& place : places) {
        place.savePlacesToFile(ofs);
    }

    ofs.close();
    cout << "Данные о залах сохранены в файл.\n";
}

void loadAllPlacesFromFile(std::vector<Place>& places, const std::vector<Subscription>& existingSubscriptions) {
    std::ifstream ifs("places.txt");
    if (!ifs) {
        std::cout << "Ошибка открытия файла для чтения!\n";
        return;
    }

    places.clear();

    while (!ifs.eof()) {
        Place tempPlace;
        tempPlace.loadPlacesFromFile(ifs, existingSubscriptions);

        // Проверяем, был ли успешно загружен зал
        if (ifs.fail() && !ifs.eof()) {
            std::cout << "Ошибка при загрузке зала.\n";
            break; // Выход из цикла, если произошла ошибка
        }

        places.push_back(tempPlace);
    }

    ifs.close();
    std::cout << "Данные о залах загружены из файла.\n";
}