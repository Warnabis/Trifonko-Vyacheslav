#include "Subscription.h"

Subscription::Subscription(int id, const std::string& name, double price)
    : id(id), name(name), price(price) {}

std::string Subscription::getName() const {
    return name;
}

double Subscription::getPrice() const {
    return price;
}

int Subscription::getId() const {
    return id;
}

void Subscription::setId(int newId) {
    id = newId;
}

void Subscription::setName(const std::string& newName) {
    name = newName;
}

void Subscription::setPrice(double newPrice) {
    price = newPrice;
}

void Subscription::activate() {
    if (!activated) {
        activated = true;
        std::cout << "Подписка \"" << name << "\" активирована." << std::endl;
    } else {
        std::cout << "Подписка \"" << name << "\" уже активирована." << std::endl;
    }
}

void Subscription::deactivate() {
    if (activated) {
        activated = false;
        std::cout << "Подписка \"" << name << "\" деактивирована." << std::endl;
    } else {
        std::cout << "Подписка \"" << name << "\" уже деактивирована." << std::endl;
    }
}

bool Subscription::isActivated() const {
    return activated;
}

void Subscription::setActivated(bool status) {
    activated = status;
}

bool operator==(const Subscription& lhs, const Subscription& rhs) {
    return lhs.price == rhs.price;
}

bool operator>(const Subscription& lhs, const Subscription& rhs) {
    return lhs.price > rhs.price;
}

std::ostream& operator<<(std::ostream& os, const Subscription& subscription) {
    os << subscription.id << ' ' << subscription.name << ' ' << subscription.price << ' ';
    return os;
}

std::istream& operator>>(std::istream& is, Subscription& subscription) {
    is >> subscription.id >> subscription.name >> subscription.price;
    return is;
}
