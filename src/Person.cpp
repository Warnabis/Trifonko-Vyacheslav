#include "Person.h"

Person::Person(const std::string& login, const std::string& password)
    : login(login), password(password) {}

std::string Person::getLogin() const {
    return login;
}

std::string Person::getPassword() const {
    return password;
}