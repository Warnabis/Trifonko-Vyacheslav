#ifndef UNLIMITEDSUBSCRIPTION_H
#define UNLIMITEDSUBSCRIPTION_H

#include "Subscription.h"

class UnlimitedSubscription : public Subscription {
private:
    int days;

public:
    UnlimitedSubscription(int id = 0, const std::string& name = "", float price = 0.0f, int days = 0)
        : Subscription(id, name, price), days(days) {}

    void display() const {
        std::cout << "Безлимитная подписка: " << name << ", цена: " << price << ", дней: " << days << std::endl;
    }

    void decrementDays() {
        if (days > 0) {
            days--;
        }
    }

    bool isExpired() const {
        return days <= 0;
    }

    
    int getDays() const {
        return days;
    }

    void setDays(int days) {
        this->days = days;
    }
};

#endif
