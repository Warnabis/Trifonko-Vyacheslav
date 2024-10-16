#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string login;
    std::string password;

public:
    Person(const std::string& login, const std::string& password); 

    std::string getLogin() const;
    std::string getPassword() const;

    void showMenu();
};

#endif