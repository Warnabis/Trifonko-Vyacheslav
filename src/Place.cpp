#include "Place.h"

Place::Place(const std::string& name, const std::string& address, const std::string& hours, bool activated)
    : name(name), address(address), hours(hours), activated(activated) {}

void Place::setName(const std::string& name) {
    this->name = name;
}

void Place::setAddress(const std::string& address) {
    this->address = address;
}

void Place::setHours(const std::string& hours) {
    this->hours = hours;
}

void Place::setSubscriptions(const std::vector<std::shared_ptr<Subscription>>& subs) {
    subscriptions = subs;
}

void Place::setActivated(bool activated) {
    this->activated = activated;
}

std::string Place::getName() const {
    return name;
}

std::string Place::getAddress() const {
    return address;
}

std::string Place::getHours() const {
    return hours;
}

bool Place::isActivated() const {
    return activated;
}

const std::vector<std::shared_ptr<Subscription>>& Place::getSubscriptions() const {
    return subscriptions;
}

void Place::activate() {
    activated = true;
}

void Place::deactivate() {
    activated = false;
}

void Place::addSubscription(const std::shared_ptr<Subscription>& sub) {
    subscriptions.push_back(sub);
}

std::ostream& operator<<(std::ostream& os, const Place& place) {
    os << "Название: " << place.name << "\n"
       << "Адрес: " << place.address << "\n"
       << "Часы работы: " << place.hours << "\n"
       << "Активирован: " << (place.activated ? "Да" : "Нет") << "\n"
       << "Подписки:\n";
    for (const auto& sub : place.subscriptions) {
        os << "  - " << sub->getName() << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Place& place) {
    std::cout << "Введите название: ";
    is >> place.name;
    std::cout << "Введите адрес: ";
    is >> place.address;
    std::cout << "Введите часы работы: ";
    is >> place.hours;
    std::cout << "Активирован? (1 - Да, 0 - Нет): ";
    int activatedInput;
    is >> activatedInput;
    place.activated = (activatedInput != 0);
    return is;
}
