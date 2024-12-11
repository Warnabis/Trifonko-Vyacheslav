#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "MainWindow.h"
#include "Functions.h"
#include "AccountManager.h"
#include "inputvalidationexception.h"
#include "Qstyle"
#include "Account.h"
#include "SubscriptionList.h"
#include "Subscription.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QWidget
{
    Q_OBJECT

public:
      explicit RegistrationWindow(std::vector<std::unique_ptr<Account>>& accounts, SubscriptionList<Subscription>* subscriptions, QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void on_createButton_clicked();
    void togglePasswordVisibility();
    void on_returnToMainButton_clicked();
    void validateInputs();

private:
    Ui::RegistrationWindow *ui;
    bool isPasswordVisible = false;
    QIcon eyeOpenIcon;
    QIcon eyeClosedIcon;
    QIcon arrowToLeftIcon;
    std::vector<std::unique_ptr<Account>>& accounts;
    SubscriptionList<Subscription>* subscriptions;

};

#endif
