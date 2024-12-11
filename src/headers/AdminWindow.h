#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <vector>
#include <memory>
#include "Subscription.h"
#include "Place.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include "User.h"
#include "Functions.h"
#include "MainMenuWindow.h"
#include "Account.h"
#include <QTextEdit>

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget {
    Q_OBJECT

public:
  explicit AdminWindow(std::vector<Place>* places, SubscriptionList<Subscription>* subscriptions, Account* currentAccount, QWidget *parent, std::vector<std::unique_ptr<Account>>& accounts);
    ~AdminWindow();

private slots:
    void on_createSubscription_clicked();
    void on_showSubscriptions_clicked();
    void on_updateSubscription_clicked();
    void on_deleteSubscription_clicked();
    void on_createPlace_clicked();
    void on_showPlaces_clicked();
    void on_updatePlace_clicked();
    void on_deletePlace_clicked();
    void on_saveAll_clicked();
    void on_download_clicked();
    void on_returnToMainMenu_clicked();

private:
    Ui::AdminWindow *ui;
    std::vector<Place>* places;
    SubscriptionList<Subscription>* subscriptions;
    std::vector<std::unique_ptr<Account>>& accounts;
    Account* currentAccount;
    QIcon arrowToLeftIcon;
    QIcon saveIcon;
    QIcon downloadIcon;
};

#endif
