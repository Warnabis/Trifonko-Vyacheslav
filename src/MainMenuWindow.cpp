#include "MainMenuWindow.h"
#include "ui_MainMenuWindow.h"
#include <QMessageBox>

MainMenuWindow::MainMenuWindow(QWidget *parent, Account* currentAccount, std::vector<std::unique_ptr<Account>>& accounts)
    : QWidget(parent), ui(new Ui::MainMenuWindow), currentAccount(currentAccount), accounts(accounts) {
    ui->setupUi(this);

    loadSubscriptions(subscriptions);
    loadPlaces(places, subscriptions);

    exitIcon = QIcon("C:/msys64/iconsforlabs/exit.png");
    plusIcon = QIcon("C:/msys64/iconsforlabs/plus.png");
    menuIcon = QIcon("C:/msys64/iconsforlabs/menu.png");
    arrowToLeftIcon = QIcon("C:/msys64/iconsforlabs/arrowtoleft.png");

    ui->addBalanceButton->setIcon(plusIcon);
    ui->exitButton->setIcon(exitIcon);
    ui->showMenu->setIcon(menuIcon);
    ui->hideMenu->setIcon(menuIcon);
    ui->returnToMainButton->setIcon(arrowToLeftIcon);
    ui->menuWidget->setVisible(false);
    ui->returnToMainButton->setToolTip("<font face='Artifakt Element Heavy' color='#007BFF'>Выйти из аккаунта</font>");

    updateButtonState();
    populatePlaceWidget();

}

MainMenuWindow::~MainMenuWindow() {
    delete ui;
}


void MainMenuWindow::restartMainMenu() {
    this->close();
    MainMenuWindow* newWindow = new MainMenuWindow(nullptr, currentAccount, accounts);
    newWindow->setWindowModality(Qt::ApplicationModal);
    newWindow->show();

}


void MainMenuWindow::on_placeWidget_itemClicked(QListWidgetItem* item) {
    int index = ui->placeWidget->row(item);

    if (index < 0 || index >= places.size()) {
        qDebug() << "Ошибка: неверный индекс места.";
        return;
    }

    Place* selectedPlace = &places[index];

    QString name = QString::fromStdString(selectedPlace->getName());
    QString address = QString::fromStdString(selectedPlace->getAddress());
    QString hours = QString::fromStdString(selectedPlace->getHours());
    QString activationStatus = selectedPlace->isActivated() ? "Активирован" : "Не активирован";

    AllPlaceInfoWindow* infoWindow = new AllPlaceInfoWindow(accounts, nullptr, selectedPlace, currentAccount);
    connect(infoWindow, &AllPlaceInfoWindow::restartMainMenu, this, &MainMenuWindow::restartMainMenu);
    infoWindow->setPlaceInfo(name, address, hours, activationStatus, selectedPlace->getSubscriptions());
    infoWindow->setWindowModality(Qt::ApplicationModal);
    infoWindow->show();
}


void MainMenuWindow::populatePlaceWidget() {
    ui->placeWidget->clear();

    if (places.empty()) {
        qDebug() << "Список мест пуст.";
        return;
    }

    for (const auto& place : places) {
        QString name = QString::fromStdString(place.getName());
        QString address = QString::fromStdString(place.getAddress());
        QString hours = QString::fromStdString(place.getHours());

        PlaceInfoWindow* placeWidget = new PlaceInfoWindow(this);
        placeWidget->setPlaceInfo(name, address, hours);

        QSize widgetSize = placeWidget->sizeHint();
        widgetSize.setHeight(widgetSize.height() + 100);
        widgetSize.setWidth(widgetSize.width()+ 10);

        QListWidgetItem* item = new QListWidgetItem(ui->placeWidget);
        item->setSizeHint(widgetSize);
        ui->placeWidget->addItem(item);
        ui->placeWidget->setItemWidget(item, placeWidget);
    }

    qDebug() << "Список мест успешно заполнен.";
}


void MainMenuWindow::showAllAccounts() {
    qDebug() << "Список всех аккаунтов:";

    for (const auto& account : accounts) {
        qDebug() << "Аккаунт:";
        qDebug() << "  Никнейм: " << QString::fromStdString(account->getLogin());
        qDebug() << "  Баланс: " << account->getBalance();

        qDebug() << "  Подписки:";
        for (const auto& sub : account->getSubscriptions()) {
            qDebug() << "    Название: " << QString::fromStdString(sub->getName());

            auto limitedSub = dynamic_cast<LimitedSubscription*>(sub);
            if (limitedSub) {
                qDebug() << "    Оставшиеся сессии: " << limitedSub->getSessions();
            } else {
                qDebug() << "    Тип подписки не поддерживает оставшиеся сессии.";
            }
        }
        qDebug() << "-----------------------------";
    }
}


void MainMenuWindow::updateAccountInfo() {
    if (currentAccount) {
        qDebug() << "Login:" << QString::fromStdString(currentAccount->getLogin());
        qDebug() << "Balance:" << currentAccount->getBalance();
        ui->loginLabel->setText("Аккаунт: " + QString::fromStdString(currentAccount->getLogin()));
        ui->balanceLabel->setText("Баланс: " + QString::number(currentAccount->getBalance(), 'f', 2.00));
    } else {
        qDebug() << "currentAccount is null!";
        ui->loginLabel->setText("Аккаунт: Неизвестно");
        ui->balanceLabel->setText("Баланс: 0.00");
    }
}


void MainMenuWindow::on_changeAccountInfo_clicked() {
    QStringList options = {"Изменить логин", "Изменить пароль", "Удалить аккаунт"};
    bool ok;

    QString choice = QInputDialog::getItem(this, "Выбор действия", "Выберите действие с аккаунтом:", options, 0, false, &ok);

    if (!ok || choice.isEmpty()) {
        return;
    }

    if (choice == "Изменить логин") {
        QString newLogin = QInputDialog::getText(this, "Изменить логин", "Введите новый логин:", QLineEdit::Normal, QString::fromStdString(currentAccount->getLogin()), &ok);
        if (!ok || newLogin.isEmpty()) {
            return;
        }

        for (const auto& account : accounts) {
            if (account->getLogin() == newLogin.toStdString()) {
                QMessageBox::warning(this, "Ошибка", "Аккаунт с таким логином уже существует.");
                return;
            }
        }

        std::string oldLogin = currentAccount->getLogin();
        currentAccount->setLogin(newLogin.toStdString());

        for (const auto& subscription : currentAccount->getSubscriptions()) {
            std::string subscriptionName = subscription->getName();

            size_t start = subscriptionName.find("[" + oldLogin + "]");
            if (start != std::string::npos) {
                subscriptionName.replace(start, oldLogin.length() + 2, "[" + newLogin.toStdString() + "]");
                subscription->setName(subscriptionName);
            }
        }

        saveAccountsToFile(accounts);
        QMessageBox::information(this, "Успех", "Логин успешно обновлён.");
    }
    else if (choice == "Изменить пароль") {
        QString newPassword = QInputDialog::getText(this, "Изменить пароль", "Введите новый пароль:", QLineEdit::Password, "", &ok);
        if (!ok || newPassword.isEmpty()) {
            return;
        }

        currentAccount->setPassword(newPassword.toStdString());
        saveAccountsToFile(accounts);
        QMessageBox::information(this, "Успех", "Пароль успешно обновлён.");
    }
    else if (choice == "Удалить аккаунт") {
        QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Подтверждение удаления", "Вы уверены, что хотите удалить аккаунт?");
        if (confirmation != QMessageBox::Yes) {
            return;
        }

        if (currentAccount == nullptr) {
            QMessageBox::warning(this, "Ошибка", "Текущий аккаунт уже удалён или повреждён.");
            return;
        }

        auto it = std::find_if(accounts.begin(), accounts.end(), [this](const std::unique_ptr<Account>& account) {
            return account.get() == currentAccount;
        });

        if (it != accounts.end()) {
            accounts.erase(it);
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось найти аккаунт для удаления.");
            return;
        }

        saveAccountsToFile(accounts);

        currentAccount = nullptr;

        QMessageBox::information(this, "Успех", "Аккаунт успешно удалён.");

        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }

}


void MainMenuWindow::updateCurrentAccountInList(std::vector<std::unique_ptr<Account>>& accounts, Account* currentAccount) {

    if (!currentAccount) {
        qDebug() << "currentAccount is null!";
        return;
    }

    for (auto& account : accounts) {

        if (account->getLogin() == currentAccount->getLogin()) {

            account->setBalance(currentAccount->getBalance());
            account->setSubscriptions(currentAccount->getSubscriptions());
            qDebug() << "Аккаунт обновлён: " << QString::fromStdString(account->getLogin());
            return;
        }
    }

    qDebug() << "Аккаунт с логином " << QString::fromStdString(currentAccount->getLogin()) << " не найден.";
}

void MainMenuWindow::updateCurrentAccount(std::vector<std::unique_ptr<Account>>& accounts, Account* currentAccount) {
    if (!currentAccount) {
        qDebug() << "currentAccount is null!";
        return;
    }

    for (auto& account : accounts) {
        if (account->getLogin() == currentAccount->getLogin()) {

            currentAccount->setBalance(account->getBalance());
            currentAccount->setSubscriptions(account->getSubscriptions());
            qDebug() << "This acc was updated: " << QString::fromStdString(currentAccount->getLogin());
            return;
        }
    }

    qDebug() << "Аккаунт с логином " << QString::fromStdString(currentAccount->getLogin()) << " не найден в списке.";
}


void MainMenuWindow::on_markSubscriptionButton_clicked() {
    QStringList subscriptionNames;
    std::vector<Subscription*> subscriptions = currentAccount->getSubscriptions();

    if (subscriptions.empty()) {
        QMessageBox::information(this, "Ошибка", "У вас нет приобретённых подписок.");
        return;
    }

    for (auto* sub : subscriptions) {
        if (sub) {
            std::string name = sub->getName();
            size_t pos = name.find('[');
            if (pos != std::string::npos) {
                name = name.substr(0, pos);
            }
            subscriptionNames << QString::fromStdString(name);
        }
    }

    bool ok;
    QString selectedSub = QInputDialog::getItem(this, "Отметка занятия", "Выберите подписку:", subscriptionNames, 0, false, &ok);

    if (ok && !selectedSub.isEmpty()) {
        bool subscriptionFound = false;

        std::vector<Subscription*> updatedSubscriptions;

        for (auto* sub : subscriptions) {
            if (sub) {
                std::string name = sub->getName();
                size_t pos = name.find('[');
                if (pos != std::string::npos) {
                    name = name.substr(0, pos);
                }

                if (QString::fromStdString(name) == selectedSub) {
                    subscriptionFound = true;

                    if (auto limitedSub = dynamic_cast<LimitedSubscription*>(sub)) {
                        if (limitedSub->getSessions() > 0) {
                            limitedSub->decrementSession();
                            QMessageBox::information(this, "Отметка", "Занятие успешно отмечено.");

                            if (limitedSub->getSessions() == 0) {
                                QMessageBox::information(this, "Подписка завершена", "Подписка завершена и удалена.");
                                continue;
                            }
                        } else {
                            QMessageBox::information(this, "Ошибка", "Подписка уже закончилась.");
                        }
                    } else if (auto unlimitedSub = dynamic_cast<UnlimitedSubscription*>(sub)) {
                        QMessageBox::information(this, "Успех", "Занятие отмечено для неограниченной подписки.");
                    }
                }

                updatedSubscriptions.push_back(sub);
            }
        }

        if (!subscriptionFound) {
            QMessageBox::information(this, "Ошибка", "Подписка не найдена.");
        } else {

            currentAccount->setSubscriptions(updatedSubscriptions);
        }
    }

    updateCurrentAccountInList(accounts, currentAccount);
    saveAccountsToFile(accounts);
}


void MainMenuWindow::on_subscriptionListButton_clicked() {

    QString subscriptions;

    auto userSubscriptions = currentAccount->getSubscriptions();
    qDebug() << "Количество подписок у аккаунта:" << userSubscriptions.size();

    for (auto *sub : userSubscriptions) {

        std::string name = sub->getName();
        size_t pos = name.find('[');
        if (pos != std::string::npos) {
            name = name.substr(0, pos);
        }

        if (auto limitedSub = dynamic_cast<LimitedSubscription*>(sub)) {
            subscriptions += QString::fromStdString(name) + " - " +
                             "Занятий осталось: " + QString::number(limitedSub->getSessions()) + "\n";
        } else if (auto unlimitedSub = dynamic_cast<UnlimitedSubscription*>(sub)) {
            subscriptions += QString::fromStdString(name) + " - " +
                             "Безлимитная подписка\n";
        } else {
            subscriptions += QString::fromStdString(name) + " - " +
                             "Неизвестный тип подписки\n";
        }
    }

    if (subscriptions.isEmpty()) {
        qDebug() << "У аккаунта нет подписок.";
    }

    QMessageBox::information(this, "Список подписок",
                             subscriptions.isEmpty() ? "У вас нет приобретённых подписок." : subscriptions);
}


void MainMenuWindow::on_cancelSubscriptionButton_clicked() {
    QStringList subscriptionNames;
    std::vector<Subscription*> subscriptions = currentAccount->getSubscriptions();

    if (subscriptions.empty()) {
        QMessageBox::information(this, "Ошибка", "У вас нет приобретённых подписок.");
        return;
    }

    for (auto *sub : subscriptions) {
        if (sub) {
            std::string name = sub->getName();
            size_t pos = name.find('[');
            if (pos != std::string::npos) {
                name = name.substr(0, pos);
            }
            subscriptionNames << QString::fromStdString(name);
        }
    }

    bool ok;
    QString selectedSub = QInputDialog::getItem(this, "Отмена подписки", "Выберите подписку:", subscriptionNames, 0, false, &ok);

    if (ok && !selectedSub.isEmpty()) {
        bool subscriptionFound = false;

        std::vector<Subscription*> updatedSubscriptions;

        for (auto *sub : subscriptions) {
            if (sub) {
                std::string name = sub->getName();
                size_t pos = name.find('[');
                if (pos != std::string::npos) {
                    name = name.substr(0, pos);
                }

                if (QString::fromStdString(name) == selectedSub) {

                    subscriptionFound = true;
                    QMessageBox::information(this, "Успех", "Подписка успешно отменена.");

                    continue;
                }
            }

            updatedSubscriptions.push_back(sub);
        }

        if (!subscriptionFound) {
            QMessageBox::information(this, "Ошибка", "Подписка не найдена.");
        } else {

            currentAccount->setSubscriptions(updatedSubscriptions);
        }
    }
    updateCurrentAccountInList(accounts, currentAccount);
    saveAccountsToFile(accounts);
}


void MainMenuWindow::on_addBalanceButton_clicked() {

    bool ok;
    double amount = QInputDialog::getDouble(this, "Добавление баланса", "Введите сумму для добавления:",
                                            0.0, 0.0, 10000.0, 2, &ok);

    if (ok && amount > 0) {

        double currentBalance = currentAccount->getBalance();

        currentAccount->setBalance(currentBalance + amount);

        ui->balanceLabel->setText(QString("Баланс: %1").arg(currentAccount->getBalance()));

        QMessageBox::information(this, "Баланс обновлён",
                                 QString("Баланс успешно пополнен на %1. Новый баланс: %2")
                                     .arg(amount).arg(currentAccount->getBalance()));
    } else {

        QMessageBox::warning(this, "Ошибка", "Введите корректную сумму.");
    }
    updateCurrentAccountInList(accounts, currentAccount);
    saveAccountsToFile(accounts);
}


void MainMenuWindow::on_showMenu_clicked() {
    updateAccountInfo();
    ui->menuWidget->setVisible(true);
    ui->showMenu->setVisible(false);
    ui->showMenu->setEnabled(false);
    ui->hideMenu->setVisible(true);
    ui->hideMenu->setEnabled(true);
}


void MainMenuWindow::on_hideMenu_clicked() {
    updateAccountInfo();
    ui->menuWidget->setVisible(false);
    ui->hideMenu->setVisible(false);
    ui->hideMenu->setEnabled(false);
    ui->showMenu->setVisible(true);
    ui->showMenu->setEnabled(true);
}


void MainMenuWindow::on_adminButton_clicked() {

    AdminWindow *adminwindow = new AdminWindow(&places, &subscriptions, currentAccount, nullptr, accounts);
    adminwindow->show();
    this->close();
}


void MainMenuWindow::updateButtonState() {
    bool isAdmin = currentAccount->getIsAdmin();
    qDebug() << "IsAdmin: " << isAdmin;

    if (isAdmin) {
        ui->adminButton->setEnabled(true);
    } else {
        ui->adminButton->setEnabled(false);
    }
}


void MainMenuWindow::on_returnToMainButton_clicked() {
    for (QWidget *widget : QApplication::topLevelWidgets()) {
        if (MainWindow* mainWindow = qobject_cast<MainWindow*>(widget)) {
            mainWindow->show();
            mainWindow->raise();
            mainWindow->activateWindow();
            this->close();
            MainWindow::restartApplication();
            return;
        }
    }

    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
    MainWindow::restartApplication();
}


void MainMenuWindow::on_exitButton_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход", "Вы уверены, что хотите выйти?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qApp->quit();
    }
}
