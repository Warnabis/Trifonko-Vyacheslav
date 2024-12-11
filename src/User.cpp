#include "User.h"

User::User(const std::string& login, const std::string& password, double balance)
    : Account(login, password, false, balance) {}


    std::string User::getAccountType() const {
    return "user";
}
