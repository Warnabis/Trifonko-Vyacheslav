
#include "User.h"
#include <iostream>

using namespace std;

void User::showMenu(const std::vector<Place>& places, const std::vector<Subscription>& subscriptions) {

    Subscription* selectedService = nullptr;
    int choice;
    do {
        std::cout << "\nМеню пользователя:\n";
        std::cout << "1. Воспользоваться услугой\n";
        std::cout << "2. Сравнить цены на услуги\n";
        std::cout << "3. Просмотреть подписки\n";
        std::cout << "4. Просмотреть залы\n";
        std::cout << "5. Выйти\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            workout(places, subscriptions, selectedService); 
            
            break;
        case 2:
            if (!subscriptions.empty()) {
                Subscription sub; 
                sub.comparePrices(subscriptions); 
            }
            else {
                std::cout << "Нет доступных услуг для сравнения." << std::endl;
                wait();
            }
            
            break;
        case 3:
            viewSubscriptions(subscriptions); 
            
            break;
        case 4:
            viewPlaces(places);  
            
            break;
        case 5:
            std::cout << "Выход из системы...\n";
            wait();
            break;
        default:
            std::cout << "Неверный выбор, попробуйте снова.\n";
            wait();
        }
    } while (choice != 5);
}

void User::viewSubscriptions(const std::vector<Subscription>& subscriptions) const {
    std::cout << "Просмотр подписок...\n";
    for (const auto& sub : subscriptions) {
        std::cout << sub.getName() << " - Активна: " << (sub.isActivated() ? "Да" : "Нет") << "\n";
    }
    wait();
}

void User::viewPlaces(const std::vector<Place>& places) const {
    std::cout << "Просмотр списка залов...\n";
    for (const auto& place : places) {
        std::cout << place.getName() << " - Адрес: " << place.getAddress() << " - Работает: " << (place.isActivated() ? "Да" : "Нет") << "\n";
    }
    wait();
}

void User::workout(const std::vector<Place>& places, const std::vector<Subscription>& subscriptions, Subscription*& selectedService) const {
    if (places.empty()) {
        cout << "Нет доступных залов для выбора." << endl;
        wait();
        return;
    }

    cout << "Выберите зал для тренировки:\n";
    for (size_t i = 0; i < places.size(); ++i) {
        cout << i + 1 << ". " << places[i].getName() << " (" << places[i].getAddress() << ")\n";
    }

    int placeChoice;
    cin >> placeChoice;

    if (placeChoice <= 0 || placeChoice > places.size()) {
        cout << "Неверный выбор зала. Возвращение в главное меню..." << endl;
        wait();
        return;
    }

    cout << "Вы выбрали зал: " << places[placeChoice - 1].getName() << ".\n";

    if (subscriptions.empty()) {
        cout << "Нет доступных услуг для выбора." << endl;
        wait();
        return;
    }

    string checkname;
    cout << "Введите название услуги для выбора: ";
    cin >> checkname;

    bool found = false;
    for (auto& service : subscriptions) {
        if (service.getName() == checkname) {
            selectedService = &const_cast<Subscription&>(service);
            cout << "Услуга \"" << selectedService->getName() << "\" выбрана." << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Услуга с названием \"" << checkname << "\" не найдена." << endl;
        wait();
        return;
    }

    if (!selectedService->isActivated()) {
        cout << "Активация услуги..." << endl;
        selectedService->activate();
    }

    int choice;
    system("cls");
    do {
        cout << "\n1. Провести тренировку\n2. Проверить статус тренировки\n3. Отменить текущую услугу\n4. Вернуться в главное меню\nВыберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (selectedService->getDays() > 0) {
                selectedService->decrementDays();
                cout << "Тренировка проведена. Осталось дней: " << selectedService->getDays() << endl;
            }
            else {
                cout << "У этой услуги больше не осталось доступных дней для тренировок." << endl;
            }
            wait();
            break;

        case 2:
            cout << "Выбранная услуга: \"" << selectedService->getName() << "\"\nОсталось дней: " << selectedService->getDays() << endl;
            wait();
            break;

        case 3:
            cout << "Выход из услуги \"" << selectedService->getName() << "\"." << endl;
            selectedService->deactivate();
            selectedService = nullptr;
            wait();
            return;

        case 4:
            cout << "Возвращение в главное меню..." << endl;
            wait();
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            wait();
            break;
        }
    } while (choice != 4);
}