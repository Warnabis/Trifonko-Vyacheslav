#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <memory>
#include <string>
#include <fstream>

class Subscription {
    int id;
    float price;
    int days;

public:
    std::string name;

    void input();
    friend void output(const Subscription& service);

    void create(std::unique_ptr<Subscription[]>& services, int& size) const;
    void read(const Subscription* services, int size) const;
    void update(Subscription* services, int size) const;
    void deletes(std::unique_ptr<Subscription[]>& services, int& size) const;
    void workout(Subscription* services, int size, Subscription*& selectedservice) const;
    void compareprices(Subscription* services, int size);

    void saveToFile(std::ofstream& ofs) const;

    void loadFromFile(std::ifstream& ifs);

    bool operator==(const Subscription& other) const;
    bool operator>(const Subscription& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Subscription& sub);

};

#endif


