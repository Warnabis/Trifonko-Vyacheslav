#include "AllPlaceInfoWindow.h"
#include "ui_AllPlaceInfoWindow.h"

AllPlaceInfoWindow::AllPlaceInfoWindow(std::vector<std::unique_ptr<Account>>& accounts, QWidget *parent, Place* selectedPlace, Account* currentAccount)
    : QWidget(parent), ui(new Ui::AllPlaceInfoWindow), place(selectedPlace), currentAccount(currentAccount), accounts(accounts) {
    ui->setupUi(this);
}

AllPlaceInfoWindow::~AllPlaceInfoWindow() {
    delete ui;
}

void AllPlaceInfoWindow::restartApplication() {
    this->close();
    AllPlaceInfoWindow* newWindow = new AllPlaceInfoWindow(accounts, parentWidget(), place, currentAccount);
    newWindow->setPlaceInfo(
        QString::fromStdString(place->getName()),
        QString::fromStdString(place->getAddress()),
        QString::fromStdString(place->getHours()),
        place->isActivated() ? "Активирован" : "Не активирован",
        place->getSubscriptions()
        );
    newWindow->setWindowModality(Qt::ApplicationModal);
    newWindow->show();
}

void AllPlaceInfoWindow::setPlaceInfo(const QString& name, const QString& address, const QString& hours, const QString& activationStatus, const std::vector<std::shared_ptr<Subscription>>& subscriptions) {

    ui->placeName->setAlignment(Qt::AlignCenter);
    ui->placeAddress->setAlignment(Qt::AlignCenter);
    ui->placeHours->setAlignment(Qt::AlignCenter);
    ui->placeActivationStatus->setAlignment(Qt::AlignCenter);

    ui->placeName->setText("Название зала: " + name);
    ui->placeAddress->setText("Адрес: " + address);
    ui->placeHours->setText("Рабочее время: " + hours);
    ui->placeActivationStatus->setText("Статус: " + activationStatus);

    ui->subsWidget->clear();

    for (const auto& subscription : subscriptions) {
        QString subscriptionInfo;
        if (dynamic_cast<UnlimitedSubscription*>(subscription.get())) {

            subscriptionInfo = QString("Название: %1\nЦена: %2\nТип: Безлимитная\n")
                                   .arg(QString::fromStdString(subscription->getName()))
                                   .arg(subscription->getPrice());
        } else if (dynamic_cast<LimitedSubscription*>(subscription.get())) {

            auto limitedSub = dynamic_cast<LimitedSubscription*>(subscription.get());
            subscriptionInfo = QString("Название: %1\nЦена: %2\nТип: Ограниченная\nОсталось занятий: %3\n")
                                   .arg(QString::fromStdString(subscription->getName()))
                                   .arg(subscription->getPrice())
                                   .arg(limitedSub->getSessions());
        }

        QListWidgetItem* item = new QListWidgetItem(subscriptionInfo);
        ui->subsWidget->addItem(item);
    }
}


void AllPlaceInfoWindow::on_buySubscriptionButton_clicked() {
    if (!place) {
        QMessageBox::critical(this, "Ошибка", "Информация о зале недоступна.");
        return;
    }

    const std::vector<std::shared_ptr<Subscription>>& availableSubscriptions = place->getSubscriptions();

    if (availableSubscriptions.empty()) {
        QMessageBox::information(this, "Ошибка", "В этом зале нет доступных подписок.");
        return;
    }

    QStringList subscriptionNames;
    for (const auto& sub : availableSubscriptions) {
        subscriptionNames << QString::fromStdString(sub->getName());
    }

    bool ok;
    QString selectedSub = QInputDialog::getItem(this, "Выбор подписки", "Выберите подписку:", subscriptionNames, 0, false, &ok);

    if (!ok) {
        return;
    }

    if (!selectedSub.isEmpty()) {
        std::shared_ptr<Subscription> selectedSubscription = nullptr;

        for (const auto& sub : availableSubscriptions) {
            if (QString::fromStdString(sub->getName()) == selectedSub) {
                selectedSubscription = sub;
                break;
            }
        }

        if (!selectedSubscription) {
            QMessageBox::information(this, "Ошибка", "Подписка не найдена.");
            return;
        }

        std::string subscriptionName = selectedSubscription->getName();
        std::string placeName = place->getName();
        std::string fullSubscriptionName = subscriptionName + "(Подписка зала " + placeName + ")[" + currentAccount->getLogin() + "]";

        const auto& userSubscriptions = currentAccount->getSubscriptions();
        for (const auto& userSubscription : userSubscriptions) {
            if (userSubscription->getName() == fullSubscriptionName) {
                QMessageBox::warning(this, "Ошибка", "Вы уже приобрели эту подписку.");
                return;
            }
        }

        double subscriptionPrice = selectedSubscription->getPrice();
        if (currentAccount->getBalance() < subscriptionPrice) {
            QMessageBox::warning(this, "Ошибка", "Недостаточно средств на балансе.");
            return;
        }

        currentAccount->setBalance(currentAccount->getBalance() - subscriptionPrice);
        selectedSubscription->setName(fullSubscriptionName);
        currentAccount->addSubscription(selectedSubscription.get());

        updateCurrentAccountInList(accounts, currentAccount);
        saveAccountsToFile(accounts);

        QMessageBox::information(this, "Успех", QString("Подписка \"%1\" успешно приобретена.")
                                                    .arg(QString::fromStdString(subscriptionName)));
    }

    emit restartMainMenu();
    this->close();
}



void AllPlaceInfoWindow::updateCurrentAccountInList(std::vector<std::unique_ptr<Account>>& accounts, Account* currentAccount) {

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


