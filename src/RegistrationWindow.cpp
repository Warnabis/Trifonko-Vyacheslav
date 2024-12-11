#include "RegistrationWindow.h"
#include "ui_RegistrationWindow.h"
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "InputValidationException.h"


RegistrationWindow::RegistrationWindow(std::vector<std::unique_ptr<Account>>& accounts, SubscriptionList<Subscription>* subscriptions, QWidget *parent)
    : QWidget(parent), ui(new Ui::RegistrationWindow), accounts(accounts), subscriptions(subscriptions)
{
    ui->setupUi(this);

    qDebug() << "Загружаем аккаунты и подписки...";
    if (subscriptions) {
        qDebug() << "Загружаем подписки...";
        loadSubscriptions(*subscriptions);
    } else {
        qDebug() << "Указатель подписок равен nullptr. Загрузка пропущена.";
    }
    loadAccounts(accounts, *subscriptions);

    connect(ui->showPasswordButton, &QPushButton::clicked, this, &RegistrationWindow::togglePasswordVisibility);
    connect(ui->loginLineEdit, &QLineEdit::textChanged, this, &RegistrationWindow::validateInputs);
    connect(ui->passwordLineEdit, &QLineEdit::textChanged, this, &RegistrationWindow::validateInputs);

    eyeOpenIcon = QIcon("C:/msys64/iconsforlabs/view.png");
    eyeClosedIcon = QIcon("C:/msys64/iconsforlabs/hide.png");
    arrowToLeftIcon = QIcon("C:/msys64/iconsforlabs/arrowtoleft.png");

    ui->showPasswordButton->setIcon(eyeClosedIcon);
    ui->returnToMainButton->setIcon(arrowToLeftIcon);

}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::validateInputs() {
    QString loginInput = ui->loginLineEdit->text();
    QString passwordInput = ui->passwordLineEdit->text();

    bool isLoginValid = true;
    bool isPasswordValid = true;

    if (loginInput.isEmpty()) {
        isLoginValid = false;
        ui->loginLineEdit->setProperty("error", false);
        ui->error1->setVisible(false);
    } else {
        try {
            InputValidationException::checkInput(loginInput);
            ui->loginLineEdit->setProperty("error", false);
            ui->error1->setVisible(false);
        } catch (const InputValidationException& e) {
            isLoginValid = false;
            ui->loginLineEdit->setProperty("error", true);
            ui->error1->setText(e.what());
            ui->error1->setVisible(true);
            qDebug() << "Ошибка ввода логина: " << e.what();
        }
    }

    if (passwordInput.isEmpty()) {
        isPasswordValid = false;
        ui->passwordLineEdit->setProperty("error", false);
        ui->error2->setVisible(false);
    } else {
        try {
            InputValidationException::checkInput(passwordInput);
            ui->passwordLineEdit->setProperty("error", false);
            ui->error2->setVisible(false);
        } catch (const InputValidationException& e) {
            isPasswordValid = false;
            ui->passwordLineEdit->setProperty("error", true);
            ui->error2->setText(e.what());
            ui->error2->setVisible(true);
            qDebug() << "Ошибка ввода пароля: " << e.what();
        }
    }

    ui->loginLineEdit->style()->unpolish(ui->loginLineEdit);
    ui->loginLineEdit->style()->polish(ui->loginLineEdit);

    ui->passwordLineEdit->style()->unpolish(ui->passwordLineEdit);
    ui->passwordLineEdit->style()->polish(ui->passwordLineEdit);

    ui->createButton->setEnabled(isLoginValid && isPasswordValid);
}

void RegistrationWindow::on_createButton_clicked()
{

    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString adminCode = ui->adminCodeLineEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    for (const auto& account : accounts) {
        if (account->getLogin() == login.toStdString()) {
            QMessageBox::warning(this, "Ошибка", "Аккаунт с таким логином уже существует.");
            return;
        }
    }

    QString accountType;
    if (!adminCode.isEmpty()) {
        if (adminCode == "adm") {
            accountType = "admin";
            QMessageBox::information(this, "Успех", "Администраторский аккаунт успешно создан.");
        } else {
            accountType = "user";
            QMessageBox::warning(this, "Код администратора неверен",
                                 "Введён неверный код администратора. Создан аккаунт обычного пользователя.");
        }
    } else {
        accountType = "user";
        QMessageBox::information(this, "Успех", "Создан аккаунт обычного пользователя.");
    }

    AccountManager accountManager;
    accountManager.appendAccountToFile(login, password, accountType);

    this->close();
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    MainWindow::restartApplication();
}

void RegistrationWindow::on_returnToMainButton_clicked() {

    for (QWidget *widget : QApplication::topLevelWidgets()) {

        if (MainWindow* mainWindow = qobject_cast<MainWindow*>(widget)) {

            mainWindow->show();
            mainWindow->raise();
            mainWindow->activateWindow();
            MainWindow::restartApplication();

            return;
        }
    }

    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    MainWindow::restartApplication();
}

void RegistrationWindow::togglePasswordVisibility() {
    if (ui->passwordLineEdit->echoMode() == QLineEdit::Password) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->showPasswordButton->setIcon(eyeOpenIcon);
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        ui->showPasswordButton->setIcon(eyeClosedIcon);
    }
}

