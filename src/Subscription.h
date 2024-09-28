#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <memory>
#include <string>

class Subscription {
public:
    int id;
    std::string name;
    float price;
    int days;


    void input();
    void output() const;

    void create(std::unique_ptr<Subscription[]>& services, int& size) const;
    void read(const Subscription* services, int size) const;
    void update(std::unique_ptr<Subscription[]>& services, int size) const;
    void deletes(std::unique_ptr<Subscription[]>& services, int& size) const;
    void workout(std::unique_ptr<Subscription[]>& services, int size, Subscription*& selectedservice) const;
};

#endif


