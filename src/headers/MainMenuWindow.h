#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "MainWindow.h"
#include "Functions.h"
#include "AccountManager.h"
#include "AdminWindow.h"
#include "inputvalidationexception.h"
#include "ui_MainMenuWindow.h"
#include "Qstyle"
#include "QInputDialog"
#include "PlaceInfoWindow.h"
#include "AllPlaceInfoWindow.h"

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainMenuWindow(QWidget *parent, Account* currentAccount, std::vector<std::unique_ptr<Account>>& accounts);
    ~MainMenuWindow();


private slots:
    void on_returnToMainButton_clicked();
    void on_exitButton_clicked();
    void on_markSubscriptionButton_clicked();
    void on_subscriptionListButton_clicked();
    void on_addBalanceButton_clicked();
    void on_cancelSubscriptionButton_clicked();
    void on_adminButton_clicked();
    void on_showMenu_clicked();
    void on_hideMenu_clicked();
    void on_changeAccountInfo_clicked();
    void on_placeWidget_itemClicked(QListWidgetItem* item);




private:
    Ui::MainMenuWindow *ui;
    Account* currentAccount;
    std::vector<Place> places;
    SubscriptionList<Subscription> subscriptions;
    std::vector<std::unique_ptr<Account>>& accounts;
    void updateAccountInfo();
    void updateButtonState();
    void showAllAccounts();
    void populatePlaceWidget();
    void updateCurrentAccountInList(std::vector<std::unique_ptr<Account>>& accounts, Account* currentAccount);
    void updateCurrentAccount(std::vector<std::unique_ptr<Account>>& accounts, Account* currentAccount);
    void restartMainMenu();
    QIcon arrowToLeftIcon;
    QIcon exitIcon;
    QIcon plusIcon;
    QIcon menuIcon;
};

#endif


