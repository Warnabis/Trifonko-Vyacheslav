#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <iostream>

class Subscription {
public:
    int id;
    std::string name;
    double price;
    int days;

    Subscription();
    void input();
    void output() const;
    void create(Subscription*& services, int& size);
    void read(const Subscription* services, int size) const;
    void update(Subscription* services, int size);
    void deletes(Subscription*& services, int& size);
    void workout(Subscription* services, int size, Subscription*& selectedservice) const;
};

void wait();
void choose(int choice, Subscription& service, Subscription*& services, int& size, Subscription*& selectedservice);

#endif
