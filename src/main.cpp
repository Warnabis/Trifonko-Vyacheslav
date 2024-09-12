#include <iostream>
#include <locale.h>
#include <string>
#include <conio.h>
#include <vector>

using namespace std;

void wait() {
    cout << "\nНажмите любую клавишу, чтобы продолжить";
    _getch();
    system("cls");
}

class Subscription {
public:
    int id;
    string name;
    int price;
    int days;

    void input() {
        cout << "Введите ID услуги: ";
        cin >> id;
        cout << "Введите название услуги: ";
        cin >> name;
        cout << "Введите цену услуги: ";
        cin >> price;
        cout << "Введите кол-во занятий в услуге: ";
        cin >> days;
        cout << endl;
    }

    void output() const {
        cout << "Айди: " << id
            << " Имя: " << name
            << " Цена: " << price
            << " Кол-во занятий в услуге: " << days
            << endl;
    }

    void create(vector<Subscription>& services) const {
        Subscription newService;
        newService.input();
        services.push_back(newService);
        cout << "Объект создан\n";
        wait();
    }

    void read(const vector<Subscription>& services) const {
        if (services.empty()) {
            cout << "Нет объектов для отображения" << endl;
            wait();
            return;
        }

        string checkName;
        cout << "Введите название услуги (или \"all\" для отображения всех): ";
        cin >> checkName;

        if (checkName == "all") {
            for (size_t i = 0; i < services.size(); i++) {
                cout << "Объект " << i + 1 << ": ";
                services[i].output();
                cout << endl;
            }
        }
        else {
            bool found = false;
            for (const auto& service : services) {
                if (service.name == checkName) {
                    service.output();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Услуга с названием \"" << checkName << "\" не найдена." << endl;
            }
        }
        wait();
    }

    void update(vector<Subscription>& services) const {
        if (services.empty()) {
            cout << "Нет объектов для обновления" << endl;
            return;
        }

        string checkName;
        cout << "Введите название услуги для обновления: ";
        cin >> checkName;

        bool found = false;
        for (auto& service : services) {
            if (service.name == checkName) {
                service.input();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Услуга с названием \"" << checkName << "\" не найдена" << endl;
        }
        wait();
    }

    void deletes(vector<Subscription>& services) const {
        if (services.empty()) {
            cout << "Нет объектов для удаления" << endl;
            wait();
            return;
        }

        string checkName;
        cout << "Введите название услуги для удаления (или \"all\" для удаления всех): ";
        cin >> checkName;

        if (checkName == "all") {
            services.clear();
            cout << "Все объекты удалены" << endl;
        }
        else {
            auto iterator = remove_if(services.begin(), services.end(),
                [&checkName](const Subscription& service) {
                    return service.name == checkName;
                });

            if (iterator != services.end()) {
                services.erase(iterator, services.end());
                cout << "Услуга \"" << checkName << "\" удалена" << endl;
            }
            else {
                cout << "Услуга с названием \"" << checkName << "\" не найдена" << endl;
            }
        }
        wait();
    }

    void workout(vector<Subscription>& services, Subscription*& selectedService) const {
        if (services.empty()) {
            cout << "Нет доступных услуг для выбора" << endl;
            wait();
            return;
        }

        if (selectedService == nullptr) {
            cout << "Услуга не выбрана. Выберите услугу перед тренировкой" << endl;
            string checkName;
            cout << "Введите название услуги для выбора: ";
            cin >> checkName;

            bool found = false;
            for (auto& service : services) {
                if (service.name == checkName) {
                    selectedService = &service;
                    cout << "Услуга \"" << selectedService->name << "\" выбрана." << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Услуга с названием \"" << checkName << "\" не найдена." << endl;
                wait();
                return;
            }
        }

        int choice;
        do {
            cout << "\n1. Провести тренировку\n"
                << "2. Проверить статус тренировки\n"
                << "3. Отменить текущую услугу\n"
                << "4. Вернуться в главное меню\n"
                << "Выберите опцию: ";

            while (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Неверный выбор. Попробуйте снова" << endl
                    << "Выберите опцию: ";
            }

            switch (choice) {
            case 1:
                if (selectedService->days > 0) {
                    selectedService->days--;
                    cout << "Тренировка проведена. Осталось дней: "
                        << selectedService->days << endl;
                }
                else {
                    cout << "У этой услуги больше не осталось доступных дней для тренировок" << endl;
                }
                wait();
                break;

            case 2:
                cout << "Выбранная услуга: \"" << selectedService->name << "\"\n"
                    << "Осталось дней: " << selectedService->days << endl;
                wait();
                break;

            case 3:
                cout << "Выход из услуги \"" << selectedService->name << "\"." << endl;
                selectedService = nullptr;
                wait();
                return;

            case 4:
                cout << "Возвращение в главное меню..." << endl;
                wait();
                break;

            default:
                cout << "Неверный выбор. Попробуйте снова" << endl;
                wait();
                break;
            }
        } while (choice != 4);
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    vector<Subscription> services;
    Subscription service;
    Subscription* selectedService = nullptr;
    int choice;

    do {
        cout << "\n1. Создать новый объект\n"
            << "2. Вывести объект(ы)\n"
            << "3. Обновить объект(ы)\n"
            << "4. Удалить объект(ы)\n"
            << "5. Управление тренировками (выбор, тренировка, статус)\n"
            << "6. Выйти из программы\n"
            << "Выберите опцию: ";

        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            service.create(services);
            break;

        case 2:
            service.read(services);
            break;

        case 3:
            service.update(services);
            break;

        case 4:
            service.deletes(services);
            break;

        case 5:
            service.workout(services, selectedService);
            break;

        case 6:
            cout << "Выход из программы..." << endl;
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова" << endl;
            break;
        }
    } while (choice != 6);

    return 0;
}
