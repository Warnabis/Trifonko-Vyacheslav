QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Account.cpp \
    src/AccountManager.cpp \
    src/Admin.cpp \
    src/AdminWindow.cpp \
    src/AllPlaceInfoWindow.cpp \
    src/Functions.cpp \
    src/InputValidationException.cpp \
    src/LimitedSubscription.cpp \
    src/LoginWindow.cpp \
    src/MainMenuWindow.cpp \
    src/MainWindow.cpp \
    src/Place.cpp \
    src/PlaceInfoWindow.cpp \
    src/RegistrationWindow.cpp \
    src/Subscription.cpp \
    src/SubscriptionList.cpp \
    src/UnlimitedSubscription.cpp \
    src/User.cpp \
    src/main.cpp

HEADERS += \
    src/headers/Account.h \
    src/headers/AccountManager.h \
    src/headers/Activation.h \
    src/headers/Admin.h \
    src/headers/AdminWindow.h \
    src/headers/AllPlaceInfoWindow.h \
    src/headers/Functions.h \
    src/headers/InputValidationException.h \
    src/headers/LimitedSubscription.h \
    src/headers/LoginWindow.h \
    src/headers/MainMenuWindow.h \
    src/headers/MainWindow.h \
    src/headers/Place.h \
    src/headers/PlaceInfoWindow.h \
    src/headers/RegistrationWindow.h \
    src/headers/Subscription.h \
    src/headers/SubscriptionList.h \
    src/headers/UnlimitedSubscription.h \
    src/headers/User.h

FORMS += \
    src/windows/AdminWindow.ui \
    src/windows/AllPlaceInfoWindow.ui \
    src/windows/LoginWindow.ui \
    src/windows/MainMenuWindow.ui \
    src/windows/MainWindow.ui \
    src/windows/PlaceInfoWindow.ui \
    src/windows/RegistrationWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
