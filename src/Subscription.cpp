#include "Subscription.h"
#include <iostream>

void Subscription::comparePrices(const std::vector<std::shared_ptr<Subscription>>& services) const {
    if (services.size() < 2) {
        std::cout << "Для сравнения цен нужно минимум две подписки.\n";
        return;
    }

    std::string name1, name2;
    std::cout << "Введите название первой подписки: ";
    std::cin >> name1;
    std::cout << "Введите название второй подписки: ";
    std::cin >> name2;

    std::shared_ptr<Subscription> sub1 = nullptr, sub2 = nullptr;

    for (const auto& sub : services) {
        if (sub->getName() == name1) {
            sub1 = sub;
        }
        else if (sub->getName() == name2) {
            sub2 = sub;
        }
    }

    if (sub1 && sub2) {
        if (*sub1 == *sub2) {
            std::cout << "Подписки \"" << name1 << "\" и \"" << name2 << "\" имеют одинаковую цену.\n";
        }
        else if (*sub1 > *sub2) {
            std::cout << "Подписка \"" << name1 << "\" дороже подписки \"" << name2 << "\".\n";
        }
        else {
            std::cout << "Подписка \"" << name2 << "\" дороже подписки \"" << name1 << "\".\n";
        }
    }
    else {
        std::cout << "Одна или обе подписки не найдены.\n";
    }
}
