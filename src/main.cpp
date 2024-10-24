#include <iostream>
#include <fstream>
#include <vector>
#include <memory> //vivod wait place fulluser updatesub
#include <iostream>
#include <vector>
#include "Admin.h"
#include "User.h"
#include "Place.h"
#include "Subscription.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include "SubscriptionList.h"
#include "Functions.h"

using namespace std;

void loadAllPlacesFromFile(vector<Place>& places, const vector<shared_ptr<Subscription>>& existingSubscriptions);
void saveAllPlacesToFile(const vector<Place>& places);
void loadAllSubscriptionsFromFile(vector<shared_ptr<Subscription>>& subscriptions);
void saveAllSubscriptionsToFile(const SubscriptionList<Subscription>& subscriptions);

void saveAllSubscriptionsToFile(const SubscriptionList<Subscription>& subscriptions) {
    ofstream ofs("subscriptions.txt");
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи подписок!" << std::endl;
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

        ofs << endl; 
    }

    ofs.close(); 
}


int main() {
    setlocale(LC_ALL, "rus");
    vector<Place> places;
    SubscriptionList<Subscription> subscriptionList;

    char loadFromFile;
    cout << "Считывать данные из файла? (y/n): ";
    cin >> loadFromFile;
    cin.ignore();

    if (loadFromFile == 'y' || loadFromFile == 'Y') {
        cout << endl;
        loadAllSubscriptionsFromFile(subscriptionList.getSubscriptions()); 
        loadAllPlacesFromFile(places, subscriptionList.getSubscriptions()); 
        wait();
    }

    int userType;
    cout << "Выберите тип пользователя:\n";
    cout << "1. Администратор\n";
    cout << "2. Обычный пользователь\n";
    cout << "Ваш выбор: ";
    cin >> userType;

    if (userType == 1) {
        string inputLogin, inputPassword;
        cout << "Введите логин: ";
        cin >> inputLogin;
        cout << "Введите пароль: ";
        cin >> inputPassword;

        Admin admin;

        if (inputLogin == admin.getLogin() && inputPassword == admin.getPassword()) {
            cout << "Успешный вход!" << endl;
            wait();
            admin.showMenu(places, subscriptionList); 

            saveAllPlacesToFile(places);
            saveAllSubscriptionsToFile(subscriptionList); 
        }
        else {
            cout << "Неверный логин или пароль!" << endl;
            wait();
        }
    }
    else if (userType == 2) {
        string inputLogin, inputPassword;
        cout << "Введите логин: ";
        cin >> inputLogin;
        cout << "Введите пароль: ";
        cin >> inputPassword;

       
        User user;

        if (inputLogin == user.getLogin() && inputPassword == user.getPassword()) {
            cout << "Успешный вход!" << endl;
            wait();
            user.showMenu(places, subscriptionList); 
        }
        else {
            cout << "Неверный логин или пароль!" << endl;
            wait();
        }
    }
    else {
        cout << "Неверный выбор! Программа завершена." << endl;
        wait();
    }

    return 0;
}
