#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include "Place.h"
#include "Subscription.h"
#include <vector>
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include <memory>
#include "SubscriptionList.h"

class Admin : public Person {
public:
    Admin(const std::string& login = "admin", const std::string& password = "admin")
        : Person(login, password) {}

    void showMenu(std::vector<Place>& places, SubscriptionList<Subscription>& subscriptionList); 

    void managePlaces(std::vector<Place>& places, SubscriptionList<Subscription>& subscriptions); 

    void manageSubscriptions(SubscriptionList<Subscription>& subscriptions); 

    void loadAllPlacesFromFile(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions); 
    void saveAllPlacesToFile(const std::vector<Place>& places); 
    void loadAllSubscriptionsFromFile(SubscriptionList<Subscription>& subscriptions); 
    void saveAllSubscriptionsToFile(const SubscriptionList<Subscription>& subscriptions); 

    void createSubscription(SubscriptionList<Subscription>& subscriptions);
    void readSubscriptions(const SubscriptionList<Subscription>& subscriptions) const; 
    void updateSubscription(SubscriptionList<Subscription>& subscriptions); 
    void deleteSubscription(SubscriptionList<Subscription>& subscriptions); 
};

#endif
