#include "Place.h"

using namespace std;

void Place::savePlacesToFile(ofstream& ofs) const {
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи мест!" << endl;
        return;
    }

    if (!name.empty() || !address.empty() || !hours.empty() || activated) {
        ofs << (name.empty() ? "N/A" : name) << "\n"
            << (address.empty() ? "N/A" : address) << "\n"
            << (hours.empty() ? "N/A" : hours) << "\n"
            << (activated ? 1 : 0) << "\n";

        size_t subscriptionCount = subscriptions.size();
        ofs << subscriptionCount << "\n";

        for (const auto& sub : subscriptions) {
            if (sub) {
                ofs << sub->getId() << "\n";
            }
        }
    }
    else {
        ofs << "N/A\nN/A\nN/A\n0\n0\n";
    }
}

void Place::loadPlacesFromFile(ifstream& ifs, const vector<shared_ptr<Subscription>>& existingSubscriptions) {
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения мест!" << endl;
        return;
    }

    if (!getline(ifs, name)) {
        cerr << "Ошибка чтения названия зала!" << endl;
        return;
    }

    if (!getline(ifs, address)) {
        cerr << "Ошибка чтения адреса зала!" << endl;
        return;
    }

    if (!getline(ifs, hours)) {
        cerr << "Ошибка чтения часов работы зала!" << endl;
        return;
    }

    int activatedInput;
    if (!(ifs >> activatedInput)) {
        cerr << "Ошибка чтения состояния активации!" << endl;
        return;
    }
    activated = (activatedInput != 0);
    ifs.ignore();

    size_t subscriptionCount;
    if (!(ifs >> subscriptionCount)) {
        cerr << "Ошибка чтения количества подписок!" << endl;
        return;
    }
    ifs.ignore();

    cout << "Загружается " << subscriptionCount << " подписок для зала " << name << endl;

    subscriptions.clear();
    for (size_t i = 0; i < subscriptionCount; ++i) {
        int subscriptionId;
        if (!(ifs >> subscriptionId)) {
            cerr << "Ошибка чтения ID подписки!" << endl;
            break;
        }
        ifs.ignore();

        auto it = find_if(existingSubscriptions.begin(), existingSubscriptions.end(),
            [&subscriptionId](const shared_ptr<Subscription>& sub) {
                return sub->getId() == subscriptionId;
            });

        if (it != existingSubscriptions.end()) {
            subscriptions.push_back(*it);
        }
        else {
            cout << "Подписка с ID " << subscriptionId << " не найдена." << endl;
        }
    }
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

void loadAllPlacesFromFile(vector<Place>& places, const vector<shared_ptr<Subscription>>& existingSubscriptions) {
    ifstream ifs("places.txt");
    if (!ifs) {
        cout << "Ошибка открытия файла для чтения!\n";
        return;
    }

    places.clear();

    while (!ifs.eof()) {
        Place tempPlace;
        tempPlace.loadPlacesFromFile(ifs, existingSubscriptions);

        if (ifs.fail() && !ifs.eof()) {
            cout << "Ошибка при загрузке зала.\n";
            break;
        }

        places.push_back(tempPlace);
    }

    ifs.close();
    cout << "Данные о залах загружены из файла.\n";
}

void Place::create(vector<Place>& places, const SubscriptionList<Subscription>& availableSubscriptions) const {
    Place newPlace;
    cout << "Введите название зала: ";
    cin >> newPlace.name;

    cout << "Введите адрес зала: ";
    cin >> newPlace.address;

    cout << "Введите время работы: ";
    cin >> newPlace.hours;

    cout << "Зал активен? (1 - да, 0 - нет): ";
    cin >> newPlace.activated;
    cin.ignore();

    vector<shared_ptr<Subscription>> selectedSubscriptions;
    string subscriptionName;

    while (true) {
        cout << "Введите название подписки (или 'end' для завершения): ";
        getline(cin, subscriptionName);

        if (subscriptionName == "end") {
            break;
        }

        auto subIt = find_if(availableSubscriptions.getSubscriptions().begin(), availableSubscriptions.getSubscriptions().end(),
            [&subscriptionName](const shared_ptr<Subscription>& sub) {
                return sub->getName() == subscriptionName;
            });
        if (subIt != availableSubscriptions.getSubscriptions().end()) {
            selectedSubscriptions.push_back(*subIt);
        }
        else {
            cout << "Подписка с именем '" << subscriptionName << "' не найдена!\n";
        }
    }

    newPlace.subscriptions = selectedSubscriptions;
    places.push_back(newPlace);
}

void Place::read(const vector<Place>& places) const {
    if (places.empty()) {
        cout << "Нет доступных мест для просмотра." << endl;
        return;
    }

    cout << "Доступные места для тренировок:\n";
    for (const auto& place : places) {
        if (!place.getName().empty()) {
            cout << "Название: " << place.getName() << "\n";
            cout << "Адрес: " << place.getAddress() << "\n";
            cout << "Время работы: " << place.getHours() << "\n";
            cout << "Доступные подписки:\n";

            for (const auto& subscription : place.getSubscriptions()) {
                cout << "  - " << subscription->getName()
                    << " (ID: " << subscription->getId()
                    << ", Цена: " << subscription->getPrice() << " руб.)\n";
            }

            cout << "-------------------------\n";
        }
    }
}

void Place::update(vector<Place>& places, const SubscriptionList<Subscription>& availableSubscriptions) const {
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

    int numSubscriptions;
    cout << "Сколько подписок вы хотите добавить? ";
    cin >> numSubscriptions;
    for (int i = 0; i < numSubscriptions; i++) {
        cout << "Доступные подписки:\n";
        for (size_t j = 0; j < availableSubscriptions.getSubscriptions().size(); j++) {
            cout << j + 1 << ". " << availableSubscriptions.getSubscriptions()[j]->getName() << "\n";
        }
        int subIndex;
        cout << "Выберите подписку по номеру: ";
        cin >> subIndex;
        if (subIndex > 0 && subIndex <= availableSubscriptions.getSubscriptions().size()) {
            placeToUpdate.addSubscription(availableSubscriptions.getSubscriptions()[subIndex - 1]);
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

    string name;
    cout << "Введите название зала для удаления: ";
    cin.ignore();
    getline(cin, name);

    auto it = remove_if(places.begin(), places.end(), [&](const Place& place) {
        return place.getName() == name;
        });

    if (it != places.end()) {
        places.erase(it, places.end());
        cout << "Зал \"" << name << "\" удалён успешно.\n";
    }
    else {
        cout << "Зал с названием \"" << name << "\" не найден.\n";
    }
}


