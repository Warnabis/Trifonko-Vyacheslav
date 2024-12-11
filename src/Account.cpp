#include "Account.h"
#include <iostream>
#include <algorithm>

Account::Account(const std::string& login, const std::string& password, bool isAdmin, double balance)
    : login(login), password(password), isAdmin(isAdmin), balance(balance) {}

Account::~Account() {
    for (Subscription* subscription : activatedSubscriptions) {
        delete subscription;
    }
    activatedSubscriptions.clear();
}

std::string Account::getLogin() const {
    return login;
}

std::string Account::getPassword() const {
    return password;
}

bool Account::getIsAdmin() const {
    return isAdmin;
}

void Account::setIsAdmin(bool adminStatus) {
    isAdmin = adminStatus;
}

double Account::getBalance() const {
    return balance;
}

void Account::setBalance(double newBalance) {
    balance = newBalance;
}

void Account::setLogin(const std::string& newLogin) {
    login = newLogin;
}

void Account::setPassword(const std::string& newPassword) {
    password = newPassword;
}

const std::vector<Subscription*>& Account::getSubscriptions() const {
    return activatedSubscriptions;
}

std::vector<Subscription*>& Account::getSubscription() {
    return activatedSubscriptions;
}

void Account::removeSubscription(int id) {
    auto it = std::remove_if(activatedSubscriptions.begin(), activatedSubscriptions.end(),
                             [id](Subscription* sub) {
                                 if (sub && sub->getId() == id) {
                                     delete sub;
                                     return true;
                                 }
                                 return false;
                             });
    activatedSubscriptions.erase(it, activatedSubscriptions.end());
}

void Account::addSubscription(Subscription* subscription) {
    for (const auto& sub : activatedSubscriptions) {
        if (sub->getName() == subscription->getName()) {
            std::cout << "Подписка с таким именем уже существует." << std::endl;
            return;
        }
    }
    activatedSubscriptions.push_back(subscription);
}

void Account::addSubscriptions(Subscription* subscription, const std::string& fullName) {
    if (subscription != nullptr) {
        activatedSubscriptions.push_back(subscription);
    } else {
        std::cerr << "Error: Tried to add a null subscription!" << std::endl;
    }
}

void Account::setSubscriptions(const std::vector<Subscription*>& newSubscriptions) {
    activatedSubscriptions = newSubscriptions;
}
