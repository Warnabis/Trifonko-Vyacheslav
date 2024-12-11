#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"
#include "Place.h"
#include "Subscription.h"
#include <vector>
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include <memory>
#include "SubscriptionList.h"

class Admin : public Account {
public:
    Admin(const std::string& login, const std::string& password, double balance);

    std::string getAccountType() const;
    using Account::getLogin;
    using Account::getPassword;
    using Account::getBalance;
};

#endif
