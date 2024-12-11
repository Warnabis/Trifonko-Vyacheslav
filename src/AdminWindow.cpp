#include "AdminWindow.h"
#include "ui_AdminWindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include "Place.h"
#include "Subscription.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <vector>
#include <memory>


AdminWindow::AdminWindow(std::vector<Place>* places, SubscriptionList<Subscription>* subscriptions, Account* currentAccount, QWidget *parent, std::vector<std::unique_ptr<Account>>& accounts)
    : QWidget(parent), ui(new Ui::AdminWindow), places(places), subscriptions(subscriptions), currentAccount(currentAccount), accounts(accounts) {
    ui->setupUi(this);

    arrowToLeftIcon = QIcon("C:/msys64/iconsforlabs/arrowtoleft.png");
    saveIcon = QIcon("C:/msys64/iconsforlabs/save.png");
    downloadIcon = QIcon("C:/msys64/iconsforlabs/download.png");

    ui->returnToMainMenu->setIcon(arrowToLeftIcon);
    ui->saveAll->setIcon(saveIcon);
    ui->download->setIcon(downloadIcon);
}

AdminWindow::~AdminWindow() {
    delete ui;
}


void AdminWindow::on_createSubscription_clicked() {
    bool ok;
    QString name = QInputDialog::getText(this, "Создание подписки", "Введите название подписки:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    int price = QInputDialog::getInt(this, "Создание подписки", "Введите цену подписки:", 0, 0, 10000, 1, &ok);
    if (!ok) return;

    QString type = QInputDialog::getItem(this, "Создание подписки", "Выберите тип подписки:", {"Limited", "Unlimited"}, 0, false, &ok);
    if (!ok) return;

    int sessions = 0;
    if (type == "Limited") {
        sessions = QInputDialog::getInt(this, "Создание подписки", "Введите количество занятий:", 0, 1, 1000, 1, &ok);
        if (!ok) return;
    }

    int id = subscriptions->size() + 1;

    std::shared_ptr<Subscription> newSubscription;
    if (type == "Limited") {
        newSubscription = std::make_shared<LimitedSubscription>(id, name.toStdString(), price, true, sessions);
    } else {
        newSubscription = std::make_shared<UnlimitedSubscription>(id, name.toStdString(), price, true);
    }

    subscriptions->getSubscriptions().push_back(newSubscription);
    QMessageBox::information(this, "Создание подписки", "Подписка успешно создана!");
}


void AdminWindow::on_updateSubscription_clicked() {
    bool ok;
    int id = QInputDialog::getInt(this, "Обновление подписки", "Введите ID подписки для обновления:", 1, 1, subscriptions->size(), 1, &ok);
    if (!ok) return;

    auto it = std::find_if(subscriptions->getSubscriptions().begin(), subscriptions->getSubscriptions().end(), [id](const std::shared_ptr<Subscription>& sub) {
        return sub->getId() == id;
    });

    if (it == subscriptions->getSubscriptions().end()) {
        QMessageBox::warning(this, "Обновление подписки", "Подписка с указанным ID не найдена.");
        return;
    }

    QString name = QInputDialog::getText(this, "Обновление подписки", "Введите новое название подписки:", QLineEdit::Normal, QString::fromStdString((*it)->getName()), &ok);
    if (!ok || name.isEmpty()) return;

    int price = QInputDialog::getInt(this, "Обновление подписки", "Введите новую цену подписки:", (*it)->getPrice(), 0, 10000, 1, &ok);
    if (!ok) return;

    QString type = QInputDialog::getItem(this, "Обновление подписки", "Выберите новый тип подписки:", {"Limited", "Unlimited"}, 0, false, &ok);
    if (!ok) return;

    int sessions = 0;
    if (type == "Limited") {
        sessions = QInputDialog::getInt(this, "Обновление подписки", "Введите новое количество занятий:", 0, 1, 1000, 1, &ok);
        if (!ok) return;
    }

    if (type == "Limited") {
        *it = std::make_shared<LimitedSubscription>((*it)->getId(), name.toStdString(), price, true, sessions);
    } else {
        *it = std::make_shared<UnlimitedSubscription>((*it)->getId(), name.toStdString(), price, true);
    }

    QMessageBox::information(this, "Обновление подписки", "Подписка успешно обновлена!");
}


void AdminWindow::on_deleteSubscription_clicked() {
    bool ok;

    int id = QInputDialog::getInt(this, "Удалить подписку", "Введите ID подписки для удаления:", 1, 1, subscriptions->size(), 1, &ok);
    if (!ok) return;

    auto& list = subscriptions->getSubscriptions();

    auto it = std::remove_if(list.begin(), list.end(), [id](const std::shared_ptr<Subscription>& sub) {
        return sub->getId() == id;
    });

    if (it == list.end()) {
        QMessageBox::warning(this, "Удалить подписку", "Подписка с указанным ID не найдена.");
        return;
    }

    list.erase(it, list.end());
    QMessageBox::information(this, "Удалить подписку", "Подписка успешно удалена!");
}


void AdminWindow::on_createPlace_clicked() {
    bool ok;
    QString name = QInputDialog::getText(this, "Создать зал", "Введите название зала:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    QString address = QInputDialog::getText(this, "Создать зал", "Введите адрес зала:", QLineEdit::Normal, "", &ok);
    if (!ok || address.isEmpty()) return;

    QString hours = QInputDialog::getText(this, "Создать зал", "Введите часы работы (например, 10:00-22:00):", QLineEdit::Normal, "", &ok);
    if (!ok || hours.isEmpty()) return;

    bool active = QMessageBox::question(this, "Создать зал", "Зал активен?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;

    Place newPlace(name.toStdString(), address.toStdString(), hours.toStdString(), active);

    if (QMessageBox::question(this, "Добавить подписки", "Хотите добавить подписки в этот зал?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        while (true) {
            QString subName = QInputDialog::getText(this, "Добавить подписку", "Введите название подписки (или оставьте пустым для завершения):", QLineEdit::Normal, "", &ok);
            if (!ok || subName.isEmpty()) break;

            auto it = std::find_if(subscriptions->getSubscriptions().begin(), subscriptions->getSubscriptions().end(), [&subName](const std::shared_ptr<Subscription>& sub) {
                return sub->getName() == subName.toStdString();
            });

            if (it != subscriptions->getSubscriptions().end()) {
                newPlace.addSubscription(*it);
            } else {
                QMessageBox::warning(this, "Добавить подписку", "Подписка с таким названием не найдена.");
            }
        }
    }

    places->push_back(newPlace);

    QMessageBox::information(this, "Создать зал", "Зал успешно создан!");
}


void AdminWindow::on_updatePlace_clicked() {
    bool ok;

    QStringList gymNames;
    for (const auto& gym : *places) {
        gymNames << QString::fromStdString(gym.getName());
    }

    QString selectedGym = QInputDialog::getItem(this, "Обновить зал", "Выберите зал для обновления:", gymNames, 0, false, &ok);
    if (!ok || selectedGym.isEmpty()) return;

    auto it = std::find_if(places->begin(), places->end(), [&selectedGym](const Place& gym) {
        return QString::fromStdString(gym.getName()) == selectedGym;
    });

    if (it == places->end()) {
        QMessageBox::warning(this, "Обновить зал", "Зал с таким названием не найден.");
        return;
    }

    QString newName = QInputDialog::getText(this, "Обновить зал", "Введите новое название зала:", QLineEdit::Normal, QString::fromStdString(it->getName()), &ok);
    if (!ok || newName.isEmpty()) return;

    QString newAddress = QInputDialog::getText(this, "Обновить зал", "Введите новый адрес зала:", QLineEdit::Normal, QString::fromStdString(it->getAddress()), &ok);
    if (!ok || newAddress.isEmpty()) return;

    QString newHours = QInputDialog::getText(this, "Обновить зал", "Введите новые часы работы:", QLineEdit::Normal, QString::fromStdString(it->getHours()), &ok);
    if (!ok || newHours.isEmpty()) return;

    bool newActive = QMessageBox::question(this, "Обновить зал", "Зал активен?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;

    it->setName(newName.toStdString());
    it->setAddress(newAddress.toStdString());
    it->setHours(newHours.toStdString());
    it->setActivated(newActive);

    if (QMessageBox::question(this, "Обновить подписки", "Хотите изменить подписки для этого зала?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QString currentSubscriptions;
        for (const auto& sub : it->getSubscriptions()) {
            currentSubscriptions += QString::fromStdString(sub->getName()) + "\n";
        }
        QString message = "Текущие подписки:\n" + currentSubscriptions + "\nХотите изменить подписки?";
        if (QMessageBox::question(this, "Изменить подписки", message, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            std::vector<std::shared_ptr<Subscription>>& subscriptionsRef = const_cast<std::vector<std::shared_ptr<Subscription>>&>(it->getSubscriptions());
            subscriptionsRef.clear();

            while (true) {
                QString subName = QInputDialog::getText(this, "Добавить подписку", "Введите название подписки (или оставьте пустым для завершения):", QLineEdit::Normal, "", &ok);
                if (!ok || subName.isEmpty()) break;

                auto subIt = std::find_if(subscriptions->getSubscriptions().begin(), subscriptions->getSubscriptions().end(), [&subName](const std::shared_ptr<Subscription>& sub) {
                    return sub->getName() == subName.toStdString();
                });

                if (subIt != subscriptions->getSubscriptions().end()) {
                    it->addSubscription(*subIt);
                } else {
                    QMessageBox::warning(this, "Добавить подписку", "Подписка с таким названием не найдена.");
                }
            }
        }
    }

    QMessageBox::information(this, "Обновить зал", "Зал успешно обновлён!");
}


void AdminWindow::on_deletePlace_clicked() {
    bool ok;

    QStringList gymNames;
    for (const auto& gym : *places) {
        gymNames << QString::fromStdString(gym.getName());
    }

    QString selectedGym = QInputDialog::getItem(this, "Удалить зал", "Выберите зал для удаления:", gymNames, 0, false, &ok);
    if (!ok || selectedGym.isEmpty()) return;

    auto it = std::find_if(places->begin(), places->end(), [&selectedGym](const Place& gym) {
        return QString::fromStdString(gym.getName()) == selectedGym;
    });

    if (it == places->end()) {
        QMessageBox::warning(this, "Удалить зал", "Зал с таким названием не найден.");
        return;
    }

    places->erase(it);

    QMessageBox::information(this, "Удалить зал", "Зал успешно удалён!");
}


void AdminWindow::on_showSubscriptions_clicked() {
    if (!subscriptions || subscriptions->empty()) {
        QMessageBox::information(this, "Просмотр подписок", "Нет доступных подписок.");
        return;
    }

    QString output = "Список доступных подписок:\n";
    for (const auto& subscription : subscriptions->getSubscriptions()) {
        output += QString("ID: %1\nНазвание: %2\nЦена: %3 руб.\n")
                      .arg(subscription->getId())
                      .arg(QString::fromStdString(subscription->getName()))
                      .arg(subscription->getPrice());

        if (auto limitedSub = std::dynamic_pointer_cast<LimitedSubscription>(subscription)) {
            output += QString("Тип: Ограниченная\nОставшиеся занятия: %1\n").arg(limitedSub->getSessions());
        } else {
            output += "Тип: Безлимитная\n";
        }
        output += "-------------------------\n";
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Просмотр подписок");

    QTextEdit* textEdit = new QTextEdit(&dialog);
    textEdit->setText(output);
    textEdit->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    dialog.setLayout(layout);
    dialog.resize(600, 400);
    dialog.exec();
}


void AdminWindow::on_showPlaces_clicked() {
    if (!places || places->empty()) {
        QMessageBox::information(nullptr, "Просмотр залов", "Нет доступных залов для просмотра.");
        return;
    }

    QString output = "Доступные залы для тренировок:\n";
    for (const auto& place : *places) {
        output += QString("Название: %1\nАдрес: %2\nВремя работы: %3\n")
                      .arg(QString::fromStdString(place.getName()))
                      .arg(QString::fromStdString(place.getAddress()))
                      .arg(QString::fromStdString(place.getHours()));
        output += "Доступные подписки:\n";
        for (const auto& subscription : place.getSubscriptions()) {
            output += QString("  - %1 (ID: %2, Цена: %3 руб.)\n")
                          .arg(QString::fromStdString(subscription->getName()))
                          .arg(subscription->getId())
                          .arg(subscription->getPrice());
        }
        output += "-------------------------\n";
    }

    QDialog dialog(this);
    dialog.setWindowTitle("Просмотр залов");

    QTextEdit* textEdit = new QTextEdit(&dialog);
    textEdit->setText(output);
    textEdit->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    dialog.setLayout(layout);
    dialog.resize(600, 400);
    dialog.exec();
}



void AdminWindow::on_returnToMainMenu_clicked() {

    MainMenuWindow* mainMenuWindow = new MainMenuWindow(this->parentWidget(), currentAccount, accounts);
    mainMenuWindow->show();
    this->close();

}


void AdminWindow::on_saveAll_clicked() {
    try {
        saveSubscriptionsToFile(*subscriptions);
        savePlacesToFile(*places);
        QMessageBox::information(this, "Сохранение данных", "Данные успешно сохранены!");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка сохранения", QString("Произошла ошибка при сохранении данных: %1").arg(e.what()));
    }
}


void AdminWindow::on_download_clicked() {
    bool ok;

    QString dataSelection = QInputDialog::getItem(this, "Выбор данных", "Что вы хотите загрузить?",
                                                  {"Все залы и подписки", "Подписки", "Залы"}, 0, false, &ok);
    if (!ok) return;

    std::vector<Place> filteredPlaces;
    std::vector<std::shared_ptr<Subscription>> filteredSubscriptions;

    if (dataSelection == "Все залы и подписки") {

        filteredPlaces = *places;
        filteredSubscriptions = subscriptions->getSubscriptions();
    } else if (dataSelection == "Подписки" || dataSelection == "Залы") {
        QString filterOption = QInputDialog::getItem(this, "Фильтрация", "Выберите действие:",
                                                     {"Все элементы", "Поиск по фильтрам"}, 0, false, &ok);
        if (!ok) return;

        if (filterOption == "Все элементы") {
            if (dataSelection == "Подписки") {
                filteredSubscriptions = subscriptions->getSubscriptions();
            } else if (dataSelection == "Залы") {
                filteredPlaces = *places;
            }
        } else if (filterOption == "Поиск по фильтрам") {

            QString filterType = QInputDialog::getItem(this, "Выбор фильтра", "Выберите фильтр:",
                                                       (dataSelection == "Подписки"
                                                            ? QStringList{"По названию", "По ID", "По цене", "По статусу", "По типу", "По всем фильтрам"}
                                                            : QStringList{"По названию", "По времени работы", "По адресу", "По статусу", "По подпискам", "По всем фильтрам"}),
                                                       0, false, &ok);
            if (!ok) return;

            if (dataSelection == "Подписки") {
                if (filterType == "По названию") {
                    QString name = QInputDialog::getText(this, "Фильтр по названию", "Введите название подписки:");
                    for (const auto& sub : subscriptions->getSubscriptions()) {
                        if (QString::fromStdString(sub->getName()).contains(name, Qt::CaseInsensitive)) {
                            filteredSubscriptions.push_back(sub);
                        }
                    }
                } else if (filterType == "По ID") {
                    QString idStr = QInputDialog::getText(this, "Фильтр по ID", "Введите ID подписки:");
                    int id = idStr.toInt(&ok);
                    if (ok) {
                        for (const auto& sub : subscriptions->getSubscriptions()) {
                            if (sub->getId() == id) {
                                filteredSubscriptions.push_back(sub);
                            }
                        }
                    }
                } else if (filterType == "По цене") {
                    QString priceStr = QInputDialog::getText(this, "Фильтр по цене", "Введите цену подписки:");
                    double price = priceStr.toDouble(&ok);
                    if (ok) {
                        for (const auto& sub : subscriptions->getSubscriptions()) {
                            if (sub->getPrice() == price) {
                                filteredSubscriptions.push_back(sub);
                            }
                        }
                    }
                } else if (filterType == "По статусу") {
                    QString activeStr = QInputDialog::getText(this, "Фильтр по статусу", "Введите статус (true/false):");
                    bool active = (activeStr.toLower() == "true");
                    for (const auto& sub : subscriptions->getSubscriptions()) {
                        if (sub->isActivated() == active) {
                            filteredSubscriptions.push_back(sub);
                        }
                    }
                } else if (filterType == "По типу") {
                    QString type = QInputDialog::getItem(this, "Фильтр по типу", "Выберите тип подписки:",
                                                         {"Limited", "Unlimited"}, 0, false, &ok);
                    if (ok) {
                        bool isLimited = (type == "Limited");
                        for (const auto& sub : subscriptions->getSubscriptions()) {
                            if ((isLimited && dynamic_cast<LimitedSubscription*>(sub.get())) ||
                                (!isLimited && dynamic_cast<UnlimitedSubscription*>(sub.get()))) {
                                filteredSubscriptions.push_back(sub);
                            }
                        }
                    }
                } else if (filterType == "По всем фильтрам") {

                    QString name = QInputDialog::getText(this, "Фильтр по названию", "Введите название подписки:");
                    QString idStr = QInputDialog::getText(this, "Фильтр по ID", "Введите ID подписки:");
                    int id = idStr.toInt(&ok);
                    QString priceStr = QInputDialog::getText(this, "Фильтр по цене", "Введите цену подписки:");
                    double price = priceStr.toDouble(&ok);
                    QString activeStr = QInputDialog::getText(this, "Фильтр по статусу", "Введите статус (true/false):");
                    bool active = (activeStr.toLower() == "true");
                    QString type = QInputDialog::getItem(this, "Фильтр по типу", "Выберите тип подписки:", {"Limited", "Unlimited"}, 0, false, &ok);
                    bool isLimited = (type == "Limited");

                    for (const auto& sub : subscriptions->getSubscriptions()) {
                        bool match = true;
                        if (!name.isEmpty() && !QString::fromStdString(sub->getName()).contains(name, Qt::CaseInsensitive)) match = false;
                        if (id > 0 && sub->getId() != id) match = false;
                        if (price > 0 && sub->getPrice() != price) match = false;
                        if (activeStr.toLower() != "true" && sub->isActivated() != active) match = false;
                        if (isLimited && !dynamic_cast<LimitedSubscription*>(sub.get())) match = false;
                        if (!isLimited && dynamic_cast<LimitedSubscription*>(sub.get())) match = false;
                        if (match) filteredSubscriptions.push_back(sub);
                    }
                }
            } else if (dataSelection == "Залы") {
                if (filterType == "По названию") {
                    QString name = QInputDialog::getText(this, "Фильтр по названию", "Введите название зала:");
                    for (const auto& place : *places) {
                        if (QString::fromStdString(place.getName()).contains(name, Qt::CaseInsensitive)) {
                            filteredPlaces.push_back(place);
                        }
                    }
                } else if (filterType == "По времени работы") {
                    QString hours = QInputDialog::getText(this, "Фильтр по времени работы", "Введите время работы (например, 10:00-22:00):");
                    for (const auto& place : *places) {
                        if (QString::fromStdString(place.getHours()).contains(hours, Qt::CaseInsensitive)) {
                            filteredPlaces.push_back(place);
                        }
                    }
                } else if (filterType == "По адресу") {
                    QString address = QInputDialog::getText(this, "Фильтр по адресу", "Введите адрес зала:");
                    for (const auto& place : *places) {
                        if (QString::fromStdString(place.getAddress()).contains(address, Qt::CaseInsensitive)) {
                            filteredPlaces.push_back(place);
                        }
                    }
                } else if (filterType == "По статусу") {
                    QString activeStr = QInputDialog::getText(this, "Фильтр по статусу", "Введите статус (true/false):");
                    bool active = (activeStr.toLower() == "true");
                    for (const auto& place : *places) {
                        if (place.isActivated() == active) {
                            filteredPlaces.push_back(place);
                        }
                    }
                } else if (filterType == "По подпискам") {
                    QStringList subscriptionNames;
                    QString input;
                    do {
                        input = QInputDialog::getText(this, "Фильтр по подпискам", "Введите название подписки (или оставьте пустым для завершения):");
                        if (!input.isEmpty()) {
                            subscriptionNames.append(input);
                        }
                    } while (!input.isEmpty());

                    for (const auto& place : *places) {
                        for (const auto& sub : place.getSubscriptions()) {
                            if (subscriptionNames.contains(QString::fromStdString(sub->getName()), Qt::CaseInsensitive)) {
                                filteredPlaces.push_back(place);
                                break;
                            }
                        }
                    }
                } else if (filterType == "По всем фильтрам") {
                    QString name = QInputDialog::getText(this, "Фильтр по названию", "Введите название зала:");
                    QString hours = QInputDialog::getText(this, "Фильтр по времени работы", "Введите время работы (например, 10:00-22:00):");
                    QString address = QInputDialog::getText(this, "Фильтр по адресу", "Введите адрес зала:");
                    QString activeStr = QInputDialog::getText(this, "Фильтр по статусу", "Введите статус (true/false):");
                    bool active = (activeStr.toLower() == "true");

                    QStringList subscriptionNames;
                    QString input;
                    do {
                        input = QInputDialog::getText(this, "Фильтр по подпискам", "Введите название подписки (или оставьте пустым для завершения):");
                        if (!input.isEmpty()) {
                            subscriptionNames.append(input);
                        }
                    } while (!input.isEmpty());

                    for (const auto& place : *places) {
                        bool match = true;
                        if (!name.isEmpty() && !QString::fromStdString(place.getName()).contains(name, Qt::CaseInsensitive)) match = false;
                        if (!hours.isEmpty() && !QString::fromStdString(place.getHours()).contains(hours, Qt::CaseInsensitive)) match = false;
                        if (!address.isEmpty() && !QString::fromStdString(place.getAddress()).contains(address, Qt::CaseInsensitive)) match = false;
                        if (activeStr.toLower() != "true" && place.isActivated() != active) match = false;

                        if (!subscriptionNames.isEmpty()) {
                            bool subscriptionMatch = false;
                            for (const auto& sub : place.getSubscriptions()) {
                                if (subscriptionNames.contains(QString::fromStdString(sub->getName()), Qt::CaseInsensitive)) {
                                    subscriptionMatch = true;
                                    break;
                                }
                            }
                            if (!subscriptionMatch) match = false;
                        }

                        if (match) filteredPlaces.push_back(place);
                    }

            }
        }
    }
}

    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить отчет", "", "*.json");
    if (fileName.isEmpty()) return;

    QJsonObject reportObject;

    if (!filteredSubscriptions.empty()) {
        QJsonArray subscriptionsArray;
        for (const auto& sub : filteredSubscriptions) {
            QJsonObject subObject;
            subObject["id"] = sub->getId();
            subObject["name"] = QString::fromStdString(sub->getName());
            subObject["price"] = sub->getPrice();
            subObject["type"] = (dynamic_cast<LimitedSubscription*>(sub.get()) ? "Limited" : "Unlimited");
            subscriptionsArray.append(subObject);
        }
        reportObject["subscriptions"] = subscriptionsArray;
    }

    if (!filteredPlaces.empty()) {
        QJsonArray placesArray;
        for (const auto& place : filteredPlaces) {
            QJsonObject placeObject;
            placeObject["name"] = QString::fromStdString(place.getName());
            placeObject["address"] = QString::fromStdString(place.getAddress());
            placeObject["hours"] = QString::fromStdString(place.getHours());
            placeObject["active"] = place.isActivated();

            QJsonArray subscriptionsArray;
            for (const auto& sub : place.getSubscriptions()) {
                QJsonObject subObject;
                subObject["id"] = sub->getId();
                subObject["name"] = QString::fromStdString(sub->getName());
                subObject["price"] = sub->getPrice();
                subscriptionsArray.append(subObject);
            }
            placeObject["subscriptions"] = subscriptionsArray;

            placesArray.append(placeObject);
        }
        reportObject["places"] = placesArray;
    }

    QJsonDocument doc(reportObject);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        QMessageBox::information(this, "Сохранено", "Данные успешно сохранены в файл.");
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
    }
}

