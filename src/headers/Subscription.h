#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <iostream>
#include <string>
#include "Activation.h"

class Subscription : virtual public Activation {
protected:
    int id;
    std::string name;
    double price;
    bool activated = false;

public:
    Subscription(int id = 0, const std::string& name = "", double price = 0.0f);
    virtual ~Subscription() = default;

    virtual void display() const = 0;
    virtual void decrementDays() = 0;
    virtual bool isExpired() const = 0;
    virtual std::string getType() const = 0;

    std::string getName() const;
    double getPrice() const;
    int getId() const;

    void setId(int newId);
    void setName(const std::string& newName);
    void setPrice(double newPrice);

    void activate() override;
    void deactivate() override;
    bool isActivated() const override;
    void setActivated(bool status);


    friend bool operator==(const Subscription& lhs, const Subscription& rhs);
    friend bool operator>(const Subscription& lhs, const Subscription& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Subscription& subscription);
    friend std::istream& operator>>(std::istream& is, Subscription& subscription);
};

#endif
