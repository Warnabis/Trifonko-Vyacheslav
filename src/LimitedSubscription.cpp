#include "LimitedSubscription.h"
#include <iostream>

LimitedSubscription::LimitedSubscription(int id, const std::string& name, float price, bool active, int sessions)
    : Subscription(id, name, price), sessions(sessions) {
    activated = active;
}

void LimitedSubscription::display() const {
    std::cout << "Ограниченная подписка: " << name << ", цена: " << price << ", занятий: " << sessions << std::endl;
}

void LimitedSubscription::decrementDays() {
    if (sessions > 0) {
        sessions--;
    }
}

bool LimitedSubscription::isExpired() const {
    return sessions <= 0;
}

int LimitedSubscription::getSessions() const {
    return sessions;
}

void LimitedSubscription::setSessions(int remainingSessions) {
    if (remainingSessions >= 0) {
        sessions = remainingSessions;
    }
}

void LimitedSubscription::decrementSession() {
    if (sessions > 0) {
        sessions--;
        std::cout << "Занятие успешно завершено. Осталось занятий: " << sessions << std::endl;

        if (sessions == 0) {
            std::cout << "Подписка завершена. Занятий больше нет." << std::endl;
            setActivated(false);
        }
    } else {
        std::cout << "Занятия по этой подписке закончились.\n";
    }
}

std::string LimitedSubscription::getType() const {
    return "Limited";
}
