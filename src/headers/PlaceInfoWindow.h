#ifndef PLACEINFOWINDOW_H
#define PLACEINFOWINDOW_H

#include <QWidget>
#include "Place.h"
#include "MainMenuWindow.h"
#include <QString>
#include <QVBoxLayout>

namespace Ui {
class PlaceInfoWindow;
}

class PlaceInfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PlaceInfoWindow(QWidget *parent = nullptr);
    ~PlaceInfoWindow();
    void setPlaceInfo(const QString &name, const QString &address, const QString &hours);

private:
    Ui::PlaceInfoWindow *ui;

};

#endif
