#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QString>
#include <vector>
#include "Account.h"

class AccountManager {
private:
    std::vector<Account> accounts;
    QString filePath = "C:/msys64/iconsforlabs/accounts.txt";

public:
    AccountManager();
    void appendAccountToFile(const QString& login, const QString& password, const QString& accountType);
};

#endif
