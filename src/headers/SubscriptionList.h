#ifndef SUBSCRIPTION_LIST_H
#define SUBSCRIPTION_LIST_H

#include <vector>
#include <memory>
#include <QDebug>
#include "Subscription.h"

template <typename T>
class SubscriptionList {
private:
    std::vector<std::shared_ptr<T>> subscriptions;

public:
    void addSubscription(std::shared_ptr<T> subscription) {

        qDebug() << "Adding subscription ID:" << subscription->getId()
        << "Name:" << QString::fromStdString(subscription->getName())
        << "Price:" << subscription->getPrice();

        subscriptions.push_back(subscription);
    }

    std::shared_ptr<T> getSubscriptionByName(std::string name) const {

        qDebug() << "Searching for subscription with name:" << name;

        for (const auto& subscription : subscriptions) {
            if (subscription->getName() == name) {
                qDebug() << "Found subscription with name:" << subscription->getName();
                return subscription;
            }
        }

        qDebug() << "No subscription found with name:" << name;
        return nullptr;
    }

    void clear() {
        subscriptions.clear();
    }

    size_t size() const {
        return subscriptions.size();
    }

    std::vector<std::shared_ptr<T>>& getSubscriptions() {
        return subscriptions;
    }

    const std::vector<std::shared_ptr<T>>& getSubscriptions() const {
        return subscriptions;
    }

    bool empty() const {
        return subscriptions.empty();
    }


    class Iterator {
    private:
        typename std::vector<std::shared_ptr<T>>::iterator it;

    public:
        Iterator(typename std::vector<std::shared_ptr<T>>::iterator iterator)
            : it(iterator) {}

        std::shared_ptr<T>& operator*() {
            return *it;
        }

        Iterator& operator++() {
            it++;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return it == other.it;
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }

    };

    Iterator begin() {
        return Iterator(subscriptions.begin());
    }

    Iterator end() {
        return Iterator(subscriptions.end());
    }

    Iterator begin() const {
        return Iterator(subscriptions.begin());
    }

    Iterator end() const {
        return Iterator(subscriptions.end());
    }
};

#endif
