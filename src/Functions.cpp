#include "Functions.h"
#include "Place.h"
#include "SubscriptionList.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

const std::string PLACE_FILE_PATH = "C:/msys64/iconsforlabs/places.txt";
const std::string SUBSCRIPTION_FILE_PATH = "C:/msys64/iconsforlabs/subscriptions.txt";
const std::string ACCOUNT_FILE_PATH = "C:/msys64/iconsforlabs/accounts.txt";

void loadPlaces(std::vector<Place>& places, SubscriptionList<Subscription>& subscriptions) {
    std::ifstream ifs(PLACE_FILE_PATH);
    if (!ifs.is_open()) {
        std::cerr << "Error opening the gym file!\n";
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << "Processing line: " << line << std::endl;

        std::stringstream ss(line);

        std::string name, address, hours, activeStr, subName;
        bool active;
        std::vector<std::string> subNames;

        if (std::getline(ss, name, ',')) {
            std::cout << "Place name: " << name << std::endl;
        }

        if (std::getline(ss, address, ',')) {
            std::cout << "Place address: " << address << std::endl;
        }

        if (std::getline(ss, hours, ',')) {
            std::cout << "Working hours: " << hours << std::endl;
        }

        if (std::getline(ss, activeStr, ',')) {
            std::cout << "Place activity: " << activeStr << std::endl;
            active = (activeStr == "true");
        }

        while (std::getline(ss, subName, ',')) {
            std::cout << "Subscription: " << subName << std::endl;
            subNames.push_back(subName);
        }

        Place place(name, address, hours, active);

        for (const std::string& subName : subNames) {
            auto sub = subscriptions.getSubscriptionByName(subName);
            if (sub) {
                place.addSubscription(sub);
            } else {
                std::cerr << "Failed to find subscription with name: " << subName << std::endl;
            }
        }

        places.push_back(place);
    }
}


void loadSubscriptions(SubscriptionList<Subscription>& subscriptions) {
    std::ifstream file(SUBSCRIPTION_FILE_PATH);
    if (!file.is_open()) {
        std::cerr << "Error opening the subscription file!\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << "Processing line: " << line << std::endl;

        std::stringstream ss(line);

        int id, remainingSessions = 0;
        std::string name, activeStr;
        double price;
        bool active;

        if (std::getline(ss, activeStr, ',')) {
            id = std::stoi(activeStr);
            std::cout << "Subscription ID: " << id << std::endl;
        }

        if (std::getline(ss, name, ',')) {
            std::cout << "Subscription name: " << name << std::endl;
        }

        if (std::getline(ss, activeStr, ',')) {
            std::cout << "Price: " << activeStr << std::endl;
            try {
                price = std::stod(activeStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: invalid price format in line: " << line << std::endl;
                continue;
            }
        }

        if (std::getline(ss, activeStr, ',')) {
            std::cout << "Activity: " << activeStr << std::endl;
            active = (activeStr == "true");
        }

        if (std::getline(ss, activeStr, ',')) {
            std::cout << "Remaining sessions: " << activeStr << std::endl;
            try {
                remainingSessions = std::stoi(activeStr);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: invalid remaining sessions format in line: " << line << std::endl;
                continue;
            }
        }

        if (remainingSessions > 0) {
            subscriptions.addSubscription(std::make_shared<LimitedSubscription>(id, name, price, active, remainingSessions));
        } else {
            subscriptions.addSubscription(std::make_shared<UnlimitedSubscription>(id, name, price, active));
        }
    }
}


void loadAccounts(std::vector<std::unique_ptr<Account>>& accounts, SubscriptionList<Subscription>& subscriptions) {
    std::ifstream ifs(ACCOUNT_FILE_PATH);
    if (!ifs.is_open()) {
        std::cerr << "Error opening the accounts file!\n";
        return;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string login, password, accountType, balanceStr, subscriptionData;
        double balance;

        if (!std::getline(ss, login, ',')) {
            std::cerr << "Error reading login from line: " << line << std::endl;
            continue;
        }

        if (!std::getline(ss, password, ',')) {
            std::cerr << "Error reading password from line: " << line << std::endl;
            continue;
        }

        if (!std::getline(ss, accountType, ',')) {
            std::cerr << "Error reading account type from line: " << line << std::endl;
            continue;
        }

        if (!std::getline(ss, balanceStr, ',')) {
            std::cerr << "Error reading balance from line: " << line << std::endl;
            continue;
        }

        try {
            balance = std::stod(balanceStr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting balance: " << balanceStr << " is not a number.\n";
            continue;
        }

        std::unique_ptr<Account> account;
        if (accountType == "admin") {
            account = std::make_unique<Admin>(login, password, balance);
        } else if (accountType == "user") {
            account = std::make_unique<User>(login, password, balance);
        } else {
            std::cerr << "Unknown account type: " << accountType << " for account " << login << "!\n";
            continue;
        }

        while (std::getline(ss, subscriptionData, ',')) {
            std::stringstream subStream(subscriptionData);
            std::string subName;
            int remainingSessions = -1;

            if (!std::getline(subStream, subName, '_')) {
                std::cerr << "Error parsing subscription data: " << subscriptionData << std::endl;
                continue;
            }

            if (!(subStream >> remainingSessions)) {
                remainingSessions = -1;
            }

            if (remainingSessions >= 0) {

                auto limitedSub = std::make_shared<LimitedSubscription>(0, subName, 0.0f, true, remainingSessions);
                account->addSubscription(limitedSub.get());
                subscriptions.addSubscription(limitedSub);
            } else {

                auto unlimitedSub = std::make_shared<UnlimitedSubscription>(0, subName, 0.0f, 0);
                account->addSubscription(unlimitedSub.get());
                subscriptions.addSubscription(unlimitedSub);
            }
        }

        accounts.push_back(std::move(account));

        const auto& loadedAccount = accounts.back();
        std::cout << "Account added: \n";
        std::cout << "  Login: " << loadedAccount->getLogin() << "\n";
        std::cout << "  Password: " << loadedAccount->getPassword() << "\n";
        std::cout << "  Type: " << (dynamic_cast<Admin*>(loadedAccount.get()) ? "Admin" : "User") << "\n";
        std::cout << "  Balance: " << loadedAccount->getBalance() << "\n";

        auto subs = loadedAccount->getSubscriptions();
        if (subs.empty()) {
            std::cout << "  Subscriptions: None\n";
        } else {
            std::cout << "  Subscriptions:\n";
            for (const auto* sub : subs) {
                std::cout << "    - " << sub->getName() << " [" << sub->getType() << "]\n";
            }
        }
    }

    std::cout << "All accounts loaded successfully.\n";
}


void saveAccountsToFile(const std::vector<std::unique_ptr<Account>>& accounts) {
    std::ofstream ofs(ACCOUNT_FILE_PATH);
    if (!ofs.is_open()) {
        std::cerr << "Error opening the accounts file for writing!\n";
        return;
    }

    for (const auto& account : accounts) {
        ofs << account->getLogin() << ","
            << account->getPassword() << ","
            << (dynamic_cast<Admin*>(account.get()) ? "admin" : "user") << ","
            << account->getBalance();

        for (const auto& sub : account->getSubscriptions()) {
            ofs << ",";
            if (auto limitedSub = dynamic_cast<LimitedSubscription*>(sub)) {
                ofs << limitedSub->getName() << "_" << limitedSub->getSessions();
            } else {
                ofs << sub->getName();
            }
        }

        ofs << "\n";
    }
}


void saveSubscriptionsToFile(const SubscriptionList<Subscription>& subscriptionList) {
    std::ofstream file(SUBSCRIPTION_FILE_PATH);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка открытия файла для записи подписок");
    }

    const auto& subscriptions = subscriptionList.getSubscriptions();
    for (const auto& subscription : subscriptions) {
        file << subscription->getId() << ","
             << subscription->getName() << ","
             << subscription->getPrice() << ","
             << (subscription->isActivated() ? "true" : "false");

        if (auto limitedSub = std::dynamic_pointer_cast<LimitedSubscription>(subscription)) {
            file << "," << limitedSub->getSessions();
        }

        file << "\n";
    }

    file.close();
}


void savePlacesToFile(const std::vector<Place>& places) {
    std::ofstream file(PLACE_FILE_PATH);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка открытия файла для записи мест");
    }

    for (const auto& place : places) {
        file << place.getName() << ","
             << place.getAddress() << ","
             << place.getHours() << ","
             << (place.isActivated() ? "true" : "false");

        const auto& subscriptions = place.getSubscriptions();
        if (!subscriptions.empty()) {
            file << ",";
            for (size_t i = 0; i < subscriptions.size(); ++i) {
                file << subscriptions[i]->getName();
                if (i < subscriptions.size() - 1) {
                    file << ",";
                }
            }
        }
        file << "\n";
    }

    file.close();
}



