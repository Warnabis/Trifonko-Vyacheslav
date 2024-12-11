#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <memory>
#include "SubscriptionList.h"
#include "Subscription.h"
#include "Place.h"
#include "Account.h"
#include "User.h"
#include "Admin.h"
#include "fstream"


void wait();
void loadPlaces(std::vector<Place>& gyms, SubscriptionList<Subscription>& subscriptions);
void loadSubscriptions(SubscriptionList<Subscription>& subscriptions);
void loadAccounts(std::vector<std::unique_ptr<Account>>& accounts, SubscriptionList<Subscription>& subscriptions);
void savePlacesToFile(const std::vector<Place>& places);
void saveSubscriptionsToFile(const SubscriptionList<Subscription>& subscriptionList);
void saveAccountsToFile(const std::vector<std::unique_ptr<Account>>& accounts);
void updateAccountInFile(std::vector<std::unique_ptr<Account>>& accounts, Account* currentAccount);

#endif
