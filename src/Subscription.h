#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>
#include <vector>
#include <fstream>

class Subscription {
    int id;
    float price;
    int days;
    std::string name;

public:
    void input();
    friend void output(const Subscription& service);

    void create(std::vector<Subscription>& services) const;
    void read(const std::vector<Subscription>& services) const;
    void update(std::vector<Subscription>& services) const;
    void deletes(std::vector<Subscription>& services) const;
    void workout(std::vector<Subscription>& services, Subscription*& selectedservice) const;
    void compareprices(const std::vector<Subscription>& services) const;

    void saveToFile(std::ofstream& ofs) const;
    void loadFromFile(std::ifstream& ifs);

    friend bool operator==(const Subscription& lhs, const Subscription& rhs);
    friend bool operator>(const Subscription& lhs, const Subscription& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Subscription& sub);
};

#endif
