#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Functions.h"
#include "Activation.h"
#include "Crud.h"


class Subscription : public Activation, public Crud<Subscription> {
private:
    int id;
    float price;
    int days;
    std::string name;
    bool activated = false;

public:
    Subscription(int id = 0, float price = 0.0f, int days = 0, const std::string& name = "")
        : id(id), price(price), days(days), name(name) {}

    friend void wait();
    void input();
    friend void output(const Subscription& service);

    std::string getname() const {return name;}

    void savetofile(std::ofstream& ofs) const;
    void loadfromfile(std::ifstream& ifs);

    using Crud<Subscription>::create;
    using Crud<Subscription>::read;
    using Crud<Subscription>::update;
    using Crud<Subscription>::deletes;
    void workout(std::vector<Subscription>& services, Subscription*& selectedservice) const;
    void compareprices(const std::vector<Subscription>& services) const;

    friend bool operator==(const Subscription& lhs, const Subscription& rhs) {
        return lhs.price == rhs.price;
    }

    friend bool operator>(const Subscription& lhs, const Subscription& rhs) {
        return lhs.price > rhs.price;
    }

    friend std::ostream& operator<<(std::ostream& os, const Subscription& sub) {
        os << "\n" << "Àéäè: " << sub.id << "\n" << "Èìÿ: " << sub.name
            << "\n" << "Öåíà: " << sub.price << "\n" << "Êîë-âî çàíÿòèé: " << sub.days << "\n";
        return os;
    }
    void activate() override {
        if (!activated) { 
            activated = true;
            std::cout << "Ïîäïèñêà \"" << name << "\" àêòèâèðîâàíà." << std::endl;
        }
        else {
            std::cout << "Ïîäïèñêà \"" << name << "\" óæå àêòèâèðîâàíà." << std::endl;
        }
    }

    void deactivate() override {
        if (activated) {
            activated = false;
            std::cout << "Ïîäïèñêà \"" << name << "\" äåàêòèâèðîâàíà." << std::endl;
        }
        else {
            std::cout << "Ïîäïèñêà \"" << name << "\" óæå äåàêòèâèðîâàíà." << std::endl;
        }
    }

    bool isactivated() const override {
        return activated;
    }
};

#endif 
