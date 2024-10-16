#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Admin.h"
#include "User.h"   
#include "Place.h"
#include "Subscription.h"
#include "Functions.h"

using namespace std;

void loadAllPlacesFromFile(std::vector<Place>& places, const std::vector<Subscription>& existingSubscriptions);
void saveAllPlacesToFile(const std::vector<Place>& places);
void loadAllSubscriptionsFromFile(std::vector<Subscription>& subscriptions);
void saveAllSubscriptionsToFile(const std::vector<Subscription>& subscriptions);

int main() {
    setlocale(LC_ALL, "rus");
    vector<Place> places;
    vector<Subscription> subscriptions;

    char loadFromFile;
    cout << "Считывать данные из файла? (y/n): ";
    cin >> loadFromFile;
    cin.ignore();

    if (loadFromFile == 'y' || loadFromFile == 'Y') {
        cout << endl;
        loadAllSubscriptionsFromFile(subscriptions);
        loadAllPlacesFromFile(places, subscriptions);
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
            admin.showMenu(places, subscriptions);

            saveAllPlacesToFile(places);
            saveAllSubscriptionsToFile(subscriptions);
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
            user.showMenu(places, subscriptions);
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

//admin user files wait