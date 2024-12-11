#include "PlaceInfoWindow.h"
#include "ui_PlaceInfoWindow.h"

PlaceInfoWindow::PlaceInfoWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlaceInfoWindow)
{
    ui->setupUi(this);

    ui->placeName->setAlignment(Qt::AlignCenter);
    ui->placeAddress->setAlignment(Qt::AlignCenter);
    ui->placeHours->setAlignment(Qt::AlignCenter);
}

PlaceInfoWindow::~PlaceInfoWindow()
{
    delete ui;
}

void PlaceInfoWindow::setPlaceInfo(const QString &name, const QString &address, const QString &hours) {

    ui->placeName->setText(name);
    ui->placeAddress->setText("Адрес: " + address);
    ui->placeHours->setText("Рабочее время: " + hours);

    ui->placeName->adjustSize();
    ui->placeAddress->adjustSize();
    ui->placeHours->adjustSize();

    ui->placeName->setMinimumWidth(ui->placeName->width() + 15);
    ui->placeAddress->setMinimumWidth(ui->placeAddress->width() + 15);
    ui->placeHours->setMinimumWidth(ui->placeHours->width() + 15);
}
