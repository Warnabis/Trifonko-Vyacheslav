#include "UnlimitedSubscription.h"
#include <iostream>

UnlimitedSubscription::UnlimitedSubscription(int id, const std::string& name, float price, int days)
    : Subscription(id, name, price), days(days) {}

void UnlimitedSubscription::display() const {
    std::cout << "Безлимитная подписка: " << name << ", цена: " << price << ", дней: " << days << std::endl;
}

void UnlimitedSubscription::decrementDays() {
    if (days > 0) {
        days--;
    }
}

bool UnlimitedSubscription::isExpired() const {
    return days <= 0;
}

int UnlimitedSubscription::getDays() const {
    return days;
}

void UnlimitedSubscription::setDays(int days) {
    this->days = days;
}

std::string UnlimitedSubscription::getType() const {
    return "Unlimited";
}
