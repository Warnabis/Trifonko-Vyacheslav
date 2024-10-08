#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Subscription {
private:
    int id;
    float price;
    int days;
    std::string name;

public:
    Subscription(int id = 0, float price = 0.0f, int days = 0, const std::string& name = "")
        : id(id), price(price), days(days), name(name) {}

    void input();
    friend void output(const Subscription& service);

    void savetofile(std::ofstream& ofs) const;
    void loadfromfile(std::ifstream& ifs);

    void create(std::vector<Subscription>& services) const;
    void read(const std::vector<Subscription>& services) const;
    void update(std::vector<Subscription>& services) const;
    void deletes(std::vector<Subscription>& services) const;
    void workout(std::vector<Subscription>& services, Subscription*& selectedservice) const;
    void compareprices(const std::vector<Subscription>& services) const;

    friend bool operator==(const Subscription& lhs, const Subscription& rhs) {
        return lhs.price == rhs.price;
    }

    friend bool operator>(const Subscription& lhs, const Subscription& rhs) {
        return lhs.price > rhs.price;
    }

    friend std::ostream& operator<<(std::ostream& os, const Subscription& sub) {
        os << "Айди: " << sub.id << ", Имя: " << sub.name
            << ", Цена: " << sub.price << ", Кол-во занятий: " << sub.days;
        return os;
    }
};

#endif
