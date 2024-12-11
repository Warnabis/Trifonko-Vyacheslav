#ifndef UNLIMITEDSUBSCRIPTION_H
#define UNLIMITEDSUBSCRIPTION_H

#include "Subscription.h"
#include "Activation.h"

class UnlimitedSubscription : public Subscription {
private:
    int days;
    bool activated = false;

public:
    UnlimitedSubscription(int id = 0, const std::string& name = "", float price = 0.0f, int days = 0);

    void display() const;
    void decrementDays();
    bool isExpired() const;
    int getDays() const;
    void setDays(int days);
    std::string getType() const override;
};

#endif
