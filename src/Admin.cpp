#include "Admin.h"
#include "Place.h"
#include "Subscription.h"
#include <iostream>
#include <fstream>

using namespace std;

void Admin::saveAllPlacesToFile(const vector<Place>& places) {
    ofstream ofs("places.txt");
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи мест!" << endl;
        wait();
        return;
    }
    for (const auto& place : places) {
        ofs << place << endl; 
    }
    wait();
    ofs.close();
  
}

void Admin::saveAllSubscriptionsToFile(const vector<Subscription>& subscriptions) {
    ofstream ofs("subscriptions.txt");
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи подписок!" << endl;
        wait();
        return;
    }
    for (const auto& subscription : subscriptions) {
        ofs << subscription << endl; // Предполагается, что оператор вывода перегружен
    }
    wait();
    ofs.close();
  
}

void Admin::showMenu(vector<Place>& places, vector<Subscription>& subscriptions) {
    int choice;
    do {
        cout << "\nМеню администратора\n";
        cout << "1. Управление залами\n";
        cout << "2. Управление подписками\n";
        cout << "3. Выйти\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            managePlaces(places, subscriptions); 
            wait();
            break;
        case 2:
            manageSubscriptions(subscriptions);
            wait();
            break;
           
        case 3:
            cout << "Выход из системы...\n";
            wait();
            break;
            
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
            wait();
        }
    } while (choice != 3);
}

void Admin::managePlaces(vector<Place>& places, vector<Subscription>& subscriptions) {
    int choice;
    do {
        cout << "\nУправление залами\n";
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
            cout << "Новая подписка добавлена" << endl;
            wait();
            break;
           
        }
        case 2:
            Place().read(places);
            wait();
            break;
           
        case 3:
            Place().update(places,subscriptions);
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

void Admin::manageSubscriptions(vector<Subscription>& subscriptions) {
    int choice;
    do {
        cout << "\nУправление подписками\n";
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
        case 1: {
            Subscription newSubscription;
            newSubscription.create(subscriptions);
            wait();
            break;
           
        }
        case 2:
            Subscription().read(subscriptions);
            wait();
            break;
          
        case 3:
            Subscription().update(subscriptions);
            wait();
            break;
           
        case 4:
            Subscription().deletes(subscriptions);
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
