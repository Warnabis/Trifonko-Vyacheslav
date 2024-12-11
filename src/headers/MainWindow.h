#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Account.h"
#include "Subscription.h"
#include "SubscriptionList.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     static void restartApplication();

private slots:
    void openRegistrationWindow();
    void openLoginWindow();
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::unique_ptr<Account>> accounts;
    SubscriptionList<Subscription> subscriptions;
};

#endif
