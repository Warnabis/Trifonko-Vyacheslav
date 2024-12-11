#ifndef LIMITEDSUBSCRIPTION_H
#define LIMITEDSUBSCRIPTION_H

#include "Subscription.h"
#include "Activation.h"

class LimitedSubscription : public Subscription {
private:
    int sessions;

public:
    LimitedSubscription(int id = 0, const std::string& name = "", float price = 0.0f, bool active = false, int sessions = 0);

    void display() const override;
    void decrementDays() override;
    bool isExpired() const override;
    int getSessions() const;
    void setSessions(int remainingSessions);
    void decrementSession();
    std::string getType() const override;
};

#endif
