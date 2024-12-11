cmake_minimum_required(VERSION 3.9)
project(QtProject)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/msys64/mingw64/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(HEADERS
    src/headers/Account.h
    src/headers/AccountManager.h
    src/headers/Activation.h
    src/headers/Admin.h
    src/headers/AdminWindow.h
    src/headers/AllPlaceInfoWindow.h
    src/headers/Functions.h
    src/headers/InputValidationException.h
    src/headers/LimitedSubscription.h
    src/headers/LoginWindow.h
    src/headers/MainMenuWindow.h
    src/headers/MainWindow.h
    src/headers/Place.h
    src/headers/PlaceInfoWindow.h
    src/headers/RegistrationWindow.h
    src/headers/Subscription.h
    src/headers/SubscriptionList.h
    src/headers/UnlimitedSubscription.h
    src/headers/User.h
)

set(SOURCES
    src/Account.cpp
    src/AccountManager.cpp
    src/Admin.cpp
    src/AdminWindow.cpp
    src/AllPlaceInfoWindow.cpp
    src/Functions.cpp
    src/InputValidationException.cpp
    src/LimitedSubscription.cpp
    src/LoginWindow.cpp
    src/MainMenuWindow.cpp
    src/MainWindow.cpp
    src/Place.cpp
    src/PlaceInfoWindow.cpp
    src/RegistrationWindow.cpp
    src/Subscription.cpp
    src/UnlimitedSubscription.cpp
    src/User.cpp
    src/main.cpp
)

set(UI_FILES
    src/windows/AdminWindow.ui
    src/windows/AllPlaceInfoWindow.ui
    src/windows/LoginWindow.ui
    src/windows/MainMenuWindow.ui
    src/windows/MainWindow.ui
    src/windows/PlaceInfoWindow.ui
    src/windows/RegistrationWindow.ui
)

qt6_add_executable(QtProject
    ${HEADERS}
    ${SOURCES}
    ${UI_FILES}
)

target_link_libraries(QtProject PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
