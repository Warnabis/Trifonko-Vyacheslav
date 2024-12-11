#include "MainWindow.h"
#include "Place.h"
#include "Subscription.h"
#include "SubscriptionList.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include <QApplication>
#include "Functions.h"
#include <fstream>
#include "User.h"


int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
