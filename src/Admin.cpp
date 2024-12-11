#include "Admin.h"

Admin::Admin(const std::string& login, const std::string& password, double balance)
    : Account(login, password, true, balance) {}

std::string Admin::getAccountType() const {
    return "admin";
}
