#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <memory>
#include "Subscription.h"
#include "SubscriptionList.h"

class Account {
protected:
    std::string login;
    std::string password;
    bool isAdmin;
    double balance;
    std::vector<Subscription*> activatedSubscriptions;

public:
    Account(const std::string& login = "", const std::string& password = "", bool isAdmin = false, double balance = 0);
    virtual ~Account();

    std::string getLogin() const;
    std::string getPassword() const;
    bool getIsAdmin() const;
    void setIsAdmin(bool adminStatus);
    double getBalance() const;
    void setBalance(double newBalance);

    void setLogin(const std::string& newLogin);
    void setPassword(const std::string& newPassword);

    const std::vector<Subscription*>& getSubscriptions() const;
    std::vector<Subscription*>& getSubscription();

    void removeSubscription(int id);
    void addSubscription(Subscription* subscription);
    void addSubscriptions(Subscription* subscription, const std::string& fullName);
    void setSubscriptions(const std::vector<Subscription*>& newSubscriptions);
};

#endif
