#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "MainWindow.h"
#include "SubscriptionList.h"
#include "Account.h"
#include <vector>
#include "Subscription.h"
#include "MainMenuWindow.h"
#include <QStyle>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(QWidget *parent, std::vector<std::unique_ptr<Account>>& accounts, SubscriptionList<Subscription>* subscriptions);

    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void togglePasswordVisibility();
    void on_returnToMainButton_clicked();
    void validateInputs();

private:
    Ui::LoginWindow *ui;
    QIcon eyeOpenIcon;
    QIcon eyeClosedIcon;
    QIcon arrowToLeftIcon;

    std::vector<std::unique_ptr<Account>>& accounts;
    SubscriptionList<Subscription>* subscriptions;
};

#endif

