#ifndef USER_H
#define USER_H

#include "Person.h"
#include "Subscription.h"
#include "Place.h"
#include <vector>

class User : public Person {
private:
    std::vector<Subscription> subscriptions;
    std::vector<Place> places;

public:
    User(const std::string& login = "user", const std::string& password = "user123")
        : Person(login, password) {}

    void showMenu(const std::vector<Place>& places, const std::vector<Subscription>& subscriptions);
    void viewSubscriptions(const std::vector<Subscription>& subscriptions) const;
    void viewPlaces(const std::vector<Place>& places) const;

    void workout(const std::vector<Place>& places, const std::vector<Subscription>& subscriptions, Subscription*& selectedService) const;
    void comparePrices(const std::vector<Subscription>& services) const;
};

#endif