#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Functions.h"
#include "Subscription.h"
#include "SubscriptionList.h"

class Place : public Activation {
private:
    std::string name;
    std::string address;
    std::string hours;
    bool activated;
    std::vector<std::shared_ptr<Subscription>> subscriptions; 

public:
    Place(const std::string& name = "", const std::string& address = "", const std::string& hours = "", bool activated = false)
        : name(name), address(address), hours(hours), activated(activated) {}

    void setName(const std::string& name) { this->name = name; }
    void setAddress(const std::string& address) { this->address = address; }
    void setHours(const std::string& hours) { this->hours = hours; }

    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getHours() const { return hours; }
    bool isActivated() const { return activated; }

    const std::vector<std::shared_ptr<Subscription>>& getSubscriptions() const { return subscriptions; }

    void activate() { activated = true; }
    void deactivate() { activated = false; }

    void addSubscription(const std::shared_ptr<Subscription>& sub) { subscriptions.push_back(sub); } 

    void create(std::vector<Place>& places, const SubscriptionList<Subscription>& availableSubscriptions) const; 
    void read(const std::vector<Place>& places) const;
    void update(std::vector<Place>& places, const SubscriptionList<Subscription>& availableSubscriptions) const; 
    void deletes(std::vector<Place>& places) const;

    void savePlacesToFile(std::ofstream& ofs) const;
    void loadPlacesFromFile(std::ifstream& ifs, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions); 
    void loadAllPlacesFromFile(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions); 
    void saveAllPlacesToFile(const std::vector<Place>& places);

    friend std::ostream& operator<<(std::ostream& os, const Place& place) {
        os << "Íàçâàíèå: " << place.name << "\n"
            << "Àäðåñ: " << place.address << "\n"
            << "×àñû ðàáîòû: " << place.hours << "\n"
            << "Àêòèâèðîâàí: " << (place.activated ? "Äà" : "Íåò") << "\n"
            << "Ïîäïèñêè:\n";
        for (const auto& sub : place.subscriptions) {
            os << "  - " << sub->getName() << "\n"; 
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Place& place) {
        std::cout << "Ââåäèòå íàçâàíèå: ";
        is >> place.name;
        std::cout << "Ââåäèòå àäðåñ: ";
        is >> place.address;
        std::cout << "Ââåäèòå ÷àñû ðàáîòû: ";
        is >> place.hours;
        std::cout << "Àêòèâèðîâàí? (1 - Äà, 0 - Íåò): ";
        int activatedInput;
        is >> activatedInput;
        place.activated = (activatedInput != 0);
        return is;
    }

};

#endif
