#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QMessageBox>
#include "AdminMenuWindow.h"
#include "functions.h"
#include "InputValidationException.h"

LoginWindow::LoginWindow(QWidget *parent, std::vector<std::unique_ptr<Account>>& accounts, SubscriptionList<Subscription>* subscriptions)
    : QWidget(parent), ui(new Ui::LoginWindow), accounts(accounts), subscriptions(subscriptions) {
    ui->setupUi(this);

    qDebug() << "Загружаем аккаунты и подписки...";
    if (subscriptions) {
        qDebug() << "Загружаем подписки...";
        loadSubscriptions(*subscriptions);
    } else {
        qDebug() << "Указатель подписок равен nullptr. Загрузка пропущена.";
    }
    loadAccounts(accounts, *subscriptions);


    connect(ui->showPasswordButton, &QPushButton::clicked, this, &LoginWindow::togglePasswordVisibility);
    connect(ui->loginLineEdit, &QLineEdit::textChanged, this, &LoginWindow::validateInputs);
    connect(ui->passwordLineEdit, &QLineEdit::textChanged, this, &LoginWindow::validateInputs);

    eyeOpenIcon = QIcon("C:/msys64/iconsforlabs/view.png");
    eyeClosedIcon = QIcon("C:/msys64/iconsforlabs/hide.png");
    arrowToLeftIcon = QIcon("C:/msys64/iconsforlabs/arrowtoleft.png");

    ui->showPasswordButton->setIcon(eyeClosedIcon);
    ui->returnToMainButton->setIcon(arrowToLeftIcon);
}

LoginWindow::~LoginWindow() {
    subscriptions->clear();
    delete ui;
}

void LoginWindow::validateInputs() {
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

    ui->loginButton->setEnabled(isLoginValid && isPasswordValid);
}

void LoginWindow::on_loginButton_clicked() {
    QString username = ui->loginLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text().trimmed();

    for (auto& account : accounts) {
        if (QString::fromStdString(account->getLogin()) == username &&
            QString::fromStdString(account->getPassword()) == password) {

            qDebug() << "Login: " << QString::fromStdString(account->getLogin());
            qDebug() << "Balance: " << QString::number(account->getBalance());
            qDebug() << "Password: " << QString::fromStdString(account->getPassword());

            MainMenuWindow* mainMenuWindow = new MainMenuWindow(nullptr, account.get(),accounts);
            mainMenuWindow->setWindowModality(Qt::ApplicationModal);
            mainMenuWindow->show();

            this->close();
            return;
        }
    }

    QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль.");
}

void LoginWindow::togglePasswordVisibility() {
    if (ui->passwordLineEdit->echoMode() == QLineEdit::Password) {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->showPasswordButton->setIcon(eyeOpenIcon);
    } else {
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        ui->showPasswordButton->setIcon(eyeClosedIcon);
    }
}

void LoginWindow::on_returnToMainButton_clicked() {
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
