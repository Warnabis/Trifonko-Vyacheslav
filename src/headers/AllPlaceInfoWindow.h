#ifndef ALLPLACEINFOWINDOW_H
#define ALLPLACEINFOWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <memory>
#include <vector>
#include "Subscription.h"
#include "SubscriptionList.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include "MainMenuWindow.h"
#include "Place.h"
#include "Account.h"
#include "Functions.h"
#include <QProcess>

namespace Ui {
class AllPlaceInfoWindow;
}

class AllPlaceInfoWindow : public QWidget {
    Q_OBJECT

public:
    explicit AllPlaceInfoWindow(std::vector<std::unique_ptr<Account>>& accounts, QWidget* parent = nullptr, Place* selectedPlace = nullptr,  Account* currentAccount = nullptr);

    ~AllPlaceInfoWindow();

    void setPlaceInfo(const QString& name, const QString& address, const QString& hours,  const QString& activationStatus, const std::vector<std::shared_ptr<Subscription>>& subscriptions);
    void restartApplication();

private:
    Ui::AllPlaceInfoWindow* ui;
    Place* place;
    Account* currentAccount;
    std::vector<std::unique_ptr<Account>>& accounts;
    void updateCurrentAccountInList(std::vector<std::unique_ptr<Account>>& accounts, Account* currentAccount);

private slots:
    void on_buySubscriptionButton_clicked();

signals:

     void restartMainMenu();

};



#endif

