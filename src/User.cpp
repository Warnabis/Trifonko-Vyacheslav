#include "User.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void User::showMenu(const vector<Place>& places, SubscriptionList<Subscription>& subscriptionList) {
    int choice;
    shared_ptr<Subscription> selectedService;

    do {
        cout << "=============================\n";
        cout << "Меню пользователя:\n";
        cout << "=============================\n\n";
        cout << "1. Просмотреть подписки\n";
        cout << "2. Выполнить тренировку\n";
        cout << "3. Сравнить цены подписок\n";
        cout << "4. Просмотреть места\n";
        cout << "5. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            viewSubscriptions(subscriptionList);
            wait();
            break;
        case 2:
            workout(places, subscriptionList, selectedService);
            wait();
            break;
        case 3:
            comparePrices(subscriptionList);
            wait();
            break;
        case 4:
            viewPlaces(places);
            wait();
            break;
        case 5:
            cout << "Выход из меню.\n";
            wait();
            break;
        default:
            cout << "Некорректный выбор. Пожалуйста, попробуйте снова.\n";
            wait();
        }
    } while (choice != 5);
}

void User::viewSubscriptions(const SubscriptionList<Subscription>& subscriptionList) const {
    if (subscriptionList.getSubscriptions().empty()) {
        cout << "У вас нет доступных подписок." << endl;
        wait();
        return;
    }

    cout << "=============================\n";
    cout << "Список ваших подписок:\n";
    cout << "=============================\n";

    for (const auto& subscription : subscriptionList.getSubscriptions()) {
        cout << "ID: " << subscription->getId() << "\n";
        cout << "Название: " << subscription->getName() << "\n";
        cout << "Цена: " << subscription->getPrice() << " руб.\n";

        if (auto limitedSub = dynamic_pointer_cast<LimitedSubscription>(subscription)) {
            cout << "Тип: Ограниченная\n";
            cout << "Оставшиеся занятия: " << limitedSub->getSessions() << "\n";
        }
        else {
            cout << "Тип: Безлимитная\n";
        }

        cout << "-------------------------\n";
    }

    cout << "=============================\n";
   
}

void User::viewPlaces(const vector<Place>& places) const {
    if (places.empty()) {
        cout << "Нет доступных мест для просмотра." << endl;
        wait();
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

void User::workout(const vector<Place>& places, const SubscriptionList<Subscription>& subscriptionList, shared_ptr<Subscription>& selectedService) const {
    if (subscriptionList.empty()) {
        cout << "Нет доступных подписок для занятий." << endl;
        wait();
        return;
    }

    cout << "Доступные подписки:\n";
    subscriptionList.displayAll();

    int subscriptionChoice;
    cout << "Выберите подписку (введите ID подписки): ";
    cin >> subscriptionChoice;

    for (const auto& subscription : subscriptionList) {
        if (subscription->getId() == subscriptionChoice) {
            selectedService = subscription;
            break;
        }
    }

    if (!selectedService) {
        cout << "Подписка не найдена." << endl;
        wait();
        return;
    }

    if (places.empty()) {
        cout << "Нет доступных мест для занятий." << endl;
        wait();
        return;
    }

    cout << "Доступные места для занятий:\n";
    for (const auto& place : places) {
        cout << place.getName() << " (" << place.getAddress() << ")\n";
    }

    string placeName;
    cout << "Введите название места для тренировки: ";
    cin.ignore();
    getline(cin, placeName);

    const Place* selectedPlace = nullptr;
    for (const auto& place : places) {
        if (place.getName() == placeName) {
            selectedPlace = &place;
            break;
        }
    }

    if (!selectedPlace) {
        cout << "Место с названием \"" << placeName << "\" не найдено. Возвращение в главное меню...\n";
        wait();
        return;
    }

    cout << "Вы выбрали место: " << selectedPlace->getName() << ".\n";

    int choice;
    do {
        cout << "\n1. Провести тренировку\n2. Проверить статус подписки\n3. Вернуться в главное меню\nВыберите действие: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1: {
            if (auto limitedSub = dynamic_cast<LimitedSubscription*>(selectedService.get())) {
                if (limitedSub->getSessions() > 0) {
                    limitedSub->decrementSession();
                    cout << "Занятие успешно проведено.\n";
                    cout << "Осталось занятий: " << limitedSub->getSessions() << "\n";
                }
                else {
                    cout << "Занятия по этой подписке закончились.\n";
                }
            }
            else {
                cout << "Это безлимитная подписка. Занятие проведено.\n";
            }
            wait();
            break;
        }
        case 2: {
            cout << "Информация о подписке: \"" << selectedService->getName() << "\"\n";
            if (auto limitedSub = dynamic_cast<LimitedSubscription*>(selectedService.get())) {
                cout << "Осталось занятий: " << limitedSub->getSessions() << "\n";
            }
            else {
                cout << "Подписка безлимитная, занятия не ограничены.\n";
            }
            wait();
            break;
        }
        case 3:
            cout << "Возвращение в главное меню...\n";
            return;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
            wait();
            break;
        }
    } while (choice != 3);
}

void User::comparePrices(const SubscriptionList<Subscription>& subscriptionList) const {
    if (subscriptionList.size() < 2) {
        cout << "Для сравнения цен нужно минимум две подписки.\n";
        wait();
        return;
    }

    string name1, name2;
    cout << "Введите название первой подписки: ";
    cin >> name1;
    cout << "Введите название второй подписки: ";
    cin >> name2;

    shared_ptr<Subscription> sub1 = nullptr;
    shared_ptr<Subscription> sub2 = nullptr;

    for (const auto& sub : subscriptionList) {
        if (sub->getName() == name1) {
            sub1 = sub;
        }
        else if (sub->getName() == name2) {
            sub2 = sub;
        }
    }

    if (sub1 && sub2) {
        if (*sub1 == *sub2) {
            cout << "Подписки \"" << name1 << "\" и \"" << name2 << "\" имеют одинаковую цену.\n";
        }
        else if (*sub1 > *sub2) {
            cout << "Подписка \"" << name1 << "\" дороже подписки \"" << name2 << "\".\n";
        }
        else {
            cout << "Подписка \"" << name2 << "\" дороже подписки \"" << name1 << "\".\n";
        }
    }
    else {
        cout << "Одна или обе подписки не найдены.\n";
    }
   
}
