#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Subscription.h"

template <typename T> class SubscriptionList;

class Place : public Activation {
private:
    std::string name;
    std::string address;
    std::string hours;
    bool activated;
    std::vector<std::shared_ptr<Subscription>> subscriptions;

public:
    Place(const std::string& name = "", const std::string& address = "", const std::string& hours = "", bool activated = false);

    void setName(const std::string& name);
    void setAddress(const std::string& address);
    void setHours(const std::string& hours);
    void setSubscriptions(const std::vector<std::shared_ptr<Subscription>>& subs);

    void setActivated(bool activated);

    std::string getName() const;
    std::string getAddress() const;
    std::string getHours() const;
    bool isActivated() const;

    const std::vector<std::shared_ptr<Subscription>>& getSubscriptions() const;

    void activate();
    void deactivate();

    void addSubscription(const std::shared_ptr<Subscription>& sub);

    friend std::ostream& operator<<(std::ostream& os, const Place& place);
    friend std::istream& operator>>(std::istream& is, Place& place);
};

#endif
