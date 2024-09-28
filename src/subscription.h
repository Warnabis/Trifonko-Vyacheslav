#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <memory>
#include <string>

using namespace std;

class Subscription {
public:
    int id;
    string name;
    float price;
    int days;

    Subscription();

    void input();
    void output() const;

    void create(unique_ptr<Subscription[]>& services, int& size) const;
    void read(const unique_ptr<Subscription[]>& services, int size) const;
    void update(unique_ptr<Subscription[]>& services, int size) const;
    void deletes(unique_ptr<Subscription[]>& services, int& size) const;
    void workout(unique_ptr<Subscription[]>& services, int size, Subscription*& selectedservice) const;
};

#endif 
