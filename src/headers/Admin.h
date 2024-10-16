#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include "Place.h"
#include "Subscription.h"
#include <vector>

class Admin : public Person {
public:
    Admin(const std::string& login = "admin", const std::string& password = "admin123")
        : Person(login, password) {}

    void showMenu(std::vector<Place>& places, std::vector<Subscription>& subscriptions);

    void managePlaces(std::vector<Place>& places, std::vector<Subscription>& subscriptions);

    void manageSubscriptions(std::vector<Subscription>& subscriptions);
    
    void loadAllPlacesFromFile(std::vector<Place>& places);
    void saveAllPlacesToFile(const std::vector<Place>& places);
    void loadAllSubscriptionsFromFile(std::vector<Subscription>& subscriptions);
    void saveAllSubscriptionsToFile(const std::vector<Subscription>& subscriptions);
};

#endif