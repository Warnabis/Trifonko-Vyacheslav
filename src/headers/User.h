#ifndef USER_H
#define USER_H

#include <memory>
#include <vector>
#include <string>
#include "Place.h"
#include "Person.h"
#include "Subscription.h"
#include "SubscriptionList.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"

class User : public Person {
    SubscriptionList<Subscription> subscriptions;

public:
   
    User(const std::string& login = "user", const std::string& password = "user")
        : Person(login, password) {} 

    using Person::getLogin;    
    using Person::getPassword; 

    void showMenu(const std::vector<Place>& places, SubscriptionList<Subscription>& subscriptionList);
    void viewSubscriptions(const SubscriptionList<Subscription>& subscriptionList) const;
    void viewPlaces(const std::vector<Place>& places) const;
    void workout(const std::vector<Place>& places, const SubscriptionList<Subscription>& subscriptionList, std::shared_ptr<Subscription>& selectedService) const;
    void comparePrices(const SubscriptionList<Subscription>& subscriptionList) const;
    void displaySubscriptionDetails(const Subscription& subscription) const;
};

#endif 
