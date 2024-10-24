#ifndef SUBSCRIPTION_LIST_H
#define SUBSCRIPTION_LIST_H

#include <vector>
#include <memory>
#include "Subscription.h"

template <typename T>
class SubscriptionList {
private:
    std::vector<std::shared_ptr<T>> subscriptions;

public:
  
    void addSubscription(const std::shared_ptr<T>& subscription) {
        subscriptions.push_back(subscription);
    }

    void displayAll() const {
        for (const auto& sub : subscriptions) {
            sub->display();
        }
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

    typename std::vector<std::shared_ptr<T>>::iterator begin() {
        return subscriptions.begin();
    }

    typename std::vector<std::shared_ptr<T>>::iterator end() {
        return subscriptions.end();
    }

    typename std::vector<std::shared_ptr<T>>::const_iterator begin() const {
        return subscriptions.begin();
    }

    typename std::vector<std::shared_ptr<T>>::const_iterator end() const {
        return subscriptions.end();
    }
};

#endif
