#include "Admin.h"
#include "Place.h"
#include "Subscription.h"
#include "SubscriptionList.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>

using namespace std;

#include "Admin.h"
#include "Place.h"

void Admin::saveAllPlacesToFile(const std::vector<Place>& places) {
    std::ofstream ofs("places.txt");
    if (!ofs) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }

    for (const auto& place : places) {
        place.savePlacesToFile(ofs);  
    }

    ofs.close();
    std::cout << "Данные о залах сохранены в файл.\n";
}

void Admin::loadAllPlacesFromFile(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions) {
    std::ifstream ifs("places.txt");
    if (!ifs) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return;
    }

    places.clear();
    while (!ifs.eof()) {
        Place tempPlace;
        tempPlace.loadPlacesFromFile(ifs, existingSubscriptions);  

        if (ifs.fail() && !ifs.eof()) {
            std::cerr << "Ошибка при загрузке зала.\n";
            break;
        }

        places.push_back(tempPlace);
    }

    ifs.close();
    std::cout << "Данные о залах загружены из файла.\n";
}


void Admin::saveAllSubscriptionsToFile(const SubscriptionList<Subscription>& subscriptions) {
    std::ofstream ofs("subscriptions.txt");
    if (!ofs) {
        std::cerr << "Ошибка открытия файла для записи подписок!" << std::endl;
        return;
    }

    for (const auto& subscription : subscriptions.getSubscriptions()) {
        
        ofs << subscription->getId() << " "
            << subscription->getName() << " "
            << subscription->getPrice() << " "
            << (dynamic_cast<const LimitedSubscription*>(subscription.get()) ? 1 : 2) << " "  
            << (subscription->isActivated() ? 1 : 0);  

        
        if (const auto* limitedSub = dynamic_cast<const LimitedSubscription*>(subscription.get())) {
            ofs << " " << limitedSub->getSessions(); 
        }
        else if (const auto* unlimitedSub = dynamic_cast<const UnlimitedSubscription*>(subscription.get())) {
            ofs << " " << unlimitedSub->getDays();
        }

        ofs << std::endl; 
    }

    ofs.close(); 
}

void loadAllSubscriptionsFromFile(vector<shared_ptr<Subscription>>& subscriptions) {
    ifstream ifs("subscriptions.txt");
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения подписок!" << endl;
        return;
    }

    while (true) {
        int id, type, isActivated;
        string name;
        double price;

        if (!(ifs >> id >> name >> price >> type >> isActivated)) break;

        if (type == 1) {  
            int sessions;
            ifs >> sessions;
            subscriptions.push_back(make_shared<LimitedSubscription>(id, name, price, sessions));
        }
        else if (type == 2) {  
            int days;
            ifs >> days;
            subscriptions.push_back(make_shared<UnlimitedSubscription>(id, name, price, days));
        }

        subscriptions.back()->setActivated(isActivated == 1); 
    }
}

void Admin::showMenu(vector<Place>& places, SubscriptionList<Subscription>& subscriptionList) {
    int choice;
    do {
        std::cout << "=============================";
        cout << "\nМеню администратора\n";
        std::cout << "=============================\n\n";
        cout << "1. Управление залами\n";
        cout << "2. Управление подписками\n";
        cout << "3. Выйти\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            managePlaces(places, subscriptionList);
            wait();
            break;
        case 2:
            manageSubscriptions(subscriptionList);
            wait();
            break;
        case 3:
            cout << "Выход из системы...\n";
            
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
            wait();
        }
    } while (choice != 3);
}

void Admin::managePlaces(vector<Place>& places, SubscriptionList<Subscription>& subscriptions) {
    int choice;
    do {
        std::cout << "=============================";
        cout << "\nУправление залами\n";
        std::cout << "=============================\n\n";
        cout << "1. Добавить новый зал\n";
        cout << "2. Просмотреть все залы\n";
        cout << "3. Обновить данные зала\n";
        cout << "4. Удалить зал\n";
        cout << "5. Сохранить данные о залах в файл\n";
        cout << "6. Вернуться в меню\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            Place newPlace;
            newPlace.create(places, subscriptions);
            cout << "Новый зал добавлен." << endl;
            wait();
            break;
        }
        case 2:
            Place().read(places);
            wait();
            break;
        case 3:
            Place().update(places, subscriptions);
            wait();
            break;
        case 4:
            Place().deletes(places);
            wait();
            break;
        case 5:
            saveAllPlacesToFile(places);
            wait();
            break;
        case 6:
            cout << "Возвращение в главное меню...\n";
            
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
            wait();
        }
    } while (choice != 6);
}

void Admin::manageSubscriptions(SubscriptionList<Subscription>& subscriptions) {
    int choice;
    do {
        std::cout << "=============================\n";
        cout << "\nУправление подписками\n";
        std::cout << "=============================\n\n";
        cout << "1. Добавить новую подписку\n";
        cout << "2. Просмотреть все подписки\n";
        cout << "3. Обновить данные подписки\n";
        cout << "4. Удалить подписку\n";
        cout << "5. Сохранить данные о подписках в файл\n";
        cout << "6. Вернуться в меню\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            createSubscription(subscriptions);
            wait();
            break;
        case 2:
            readSubscriptions(subscriptions);
            wait();
            break;
        case 3:
            updateSubscription(subscriptions);
            wait();
            break;
        case 4:
            deleteSubscription(subscriptions);
            wait();
            break;
        case 5:
            saveAllSubscriptionsToFile(subscriptions); 
            wait();
            break;
        case 6:
            cout << "Возвращение в главное меню...\n";
            
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
            wait();
        }
    } while (choice != 6);
}

void Admin::createSubscription(SubscriptionList<Subscription>& subscriptions) {
    int id, type;
    string name;
    double price;

    cout << "Введите ID подписки: ";
    cin >> id;
    cout << "Введите название подписки: ";
    cin >> name;
    cout << "Введите цену подписки: ";
    cin >> price;

    cout << "Выберите тип подписки (1 - Ограниченная, 2 - Безлимитная): ";
    cin >> type;

    shared_ptr<Subscription> newSub;
    if (type == 1) {
        int sessions;
        cout << "Введите количество занятий: ";
        cin >> sessions;
        newSub = make_shared<LimitedSubscription>(id, name, price, sessions);
    }
    else if (type == 2) {
        int days;
        cout << "Введите количество дней: ";
        cin >> days;
        newSub = make_shared<UnlimitedSubscription>(id, name, price, days);
    }
    else {
        cout << "Некорректный тип подписки.\n";
        wait();
        return;
    }

    subscriptions.addSubscription(newSub);
   
}

void Admin::updateSubscription(SubscriptionList<Subscription>& subscriptions) {
    cout << "Введите ID подписки для обновления: ";
    int id;
    cin >> id;

    for (size_t i = 0; i < subscriptions.getSubscriptions().size(); i++) {
        auto& subscription = subscriptions.getSubscriptions()[i];
        if (subscription->getId() == id) {
            string name;
            double newPrice;
            int type;

            cout << "Введите новое название подписки: ";
            cin.ignore(); 
            getline(cin, name);
            cout << "Введите новую цену подписки: ";
            cin >> newPrice;

            cout << "Выберите тип подписки (1 - Ограниченная, 2 - Безлимитная): ";
            cin >> type;

            shared_ptr<Subscription> updatedSub;
            if (type == 1) {
                int sessions;
                cout << "Введите новое количество занятий: ";
                cin >> sessions;
                updatedSub = make_shared<LimitedSubscription>(id, name, newPrice, sessions);
            }
            else if (type == 2) {
                int days;
                cout << "Введите новое количество дней: ";
                cin >> days;
                updatedSub = make_shared<UnlimitedSubscription>(id, name, newPrice, days);
            }
            else {
                cout << "Некорректный тип подписки.\n";
                wait();
                return;
            }

            subscriptions.getSubscriptions()[i] = updatedSub;

            cout << "Подписка успешно обновлена." << endl;
            wait();
            return;
        }
    }
    cout << "Подписка не найдена." << endl;
   
}



void Admin::deleteSubscription(SubscriptionList<Subscription>& subscriptions) {
    cout << "Введите ID подписки для удаления: ";
    int id;
    cin >> id;

    auto& subs = subscriptions.getSubscriptions();
    auto it = std::remove_if(subs.begin(), subs.end(),
        [&](const shared_ptr<Subscription>& subscription) {
            return subscription->getId() == id;
        });

    if (it != subs.end()) {
        subs.erase(it, subs.end());
        cout << "Подписка успешно удалена." << endl;
    }
    else {
        cout << "Подписка не найдена." << endl;
    }
   
}

void Admin::readSubscriptions(const SubscriptionList<Subscription>& subscriptions) const {

    if (subscriptions.getSubscriptions().empty()) {
        std::cout << "Нет доступных подписок." << std::endl;
        wait();
        return;
    }

    std::cout << "=============================\n";
    std::cout << "Список доступных подписок:\n";
    std::cout << "=============================\n";

    for (const auto& subscription : subscriptions.getSubscriptions()) {
        std::cout << "ID: " << subscription->getId() << "\n";
        std::cout << "Название: " << subscription->getName() << "\n";
        std::cout << "Цена: " << subscription->getPrice() << " руб.\n";

        if (auto limitedSub = dynamic_pointer_cast<LimitedSubscription>(subscription)) {
            std::cout << "Тип: Ограниченная\n";
            std::cout << "Оставшиеся занятия: " << limitedSub->getSessions() << "\n";
        }
        else {
            std::cout << "Тип: Безлимитная\n";
        }

        std::cout << "-------------------------\n";
    }

    std::cout << "=============================\n";
}
    
