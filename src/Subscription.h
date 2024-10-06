#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <memory>
#include <string>
#include <fstream>

class Subscription {
    int id;
    float price;
    int days;
    std::string name;

public:

    void input();
    friend void output(const Subscription& service);

    void create(std::unique_ptr<Subscription[]>& services, int& size) const;
    void read(const Subscription* services, int size) const;
    void update(Subscription* services, int size) const;
    void deletes(std::unique_ptr<Subscription[]>& services, int& size) const;
    void workout(Subscription* services, int size, Subscription*& selectedservice) const;
    void compareprices(Subscription* services, int size) const;

    void saveToFile(std::ofstream& ofs) const;

    void loadFromFile(std::ifstream& ifs);

    friend bool operator==(const Subscription& lhs, const Subscription& rhs);
    friend bool operator>(const Subscription& lhs, const Subscription& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Subscription& sub);
};

#endif
