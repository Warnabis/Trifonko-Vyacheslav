#ifndef LIMITEDSUBSCRIPTION_H
#define LIMITEDSUBSCRIPTION_H

#include "Subscription.h"

class LimitedSubscription : public Subscription {
private:
    int sessions;

public:
    LimitedSubscription(int id = 0, const std::string& name = "", float price = 0.0f, int sessions = 0)
        : Subscription(id, name, price), sessions(sessions) {}

    void display() const override { 
        std::cout << "Ограниченная подписка: " << name << ", цена: " << price << ", занятий: " << sessions << std::endl;
    }

    void decrementDays() override { 
       
        if (sessions > 0) {
            sessions--;
        }
    }

    bool isExpired() const override { 
        return sessions <= 0;
    }

    

    int getSessions() const {
        return sessions;
    }

    void decrementSession() {
        if (sessions > 0) {
            sessions--;
            std::cout << "Занятие успешно завершено. Осталось занятий: " << sessions << std::endl;
        }
        else {
            std::cout << "Занятия по этой подписке закончились.\n";
        }
    }
};

#endif
