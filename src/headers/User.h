#ifndef USER_H
#define USER_H

#include <memory>
#include <vector>
#include <string>
#include "Place.h"
#include "Account.h"
#include "Subscription.h"
#include "SubscriptionList.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include "Functions.h"

class User : public Account {
    SubscriptionList<Subscription> subscriptions;

public:
    User(const std::string& login, const std::string& password, double balance);

    std::string getAccountType() const;
    using Account::getLogin;
    using Account::getPassword;
    using Account::getBalance;
};

#endif
