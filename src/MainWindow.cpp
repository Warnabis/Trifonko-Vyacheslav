#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "RegistrationWindow.h"
#include "LoginWindow.h"
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::openLoginWindow);
    connect(ui->registrationButton, &QPushButton::clicked, this, &MainWindow::openRegistrationWindow);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openLoginWindow() {
    LoginWindow *logins = new LoginWindow(nullptr, accounts, &subscriptions);
    logins->show();
    this->close();
}



void MainWindow::openRegistrationWindow() {

    RegistrationWindow *reg = new RegistrationWindow(accounts, &subscriptions);
    reg->show();
    this->close();
}

void MainWindow::on_exitButton_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход", "Вы уверены, что хотите выйти?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        qApp->quit();
    }
}

void MainWindow::restartApplication() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
