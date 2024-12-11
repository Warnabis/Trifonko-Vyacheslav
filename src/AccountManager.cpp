#include "AccountManager.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

AccountManager::AccountManager() {

}
void AccountManager::appendAccountToFile(const QString& login, const QString& password, const QString& accountType) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream stream(&file);

    if (!file.atEnd()) {
        stream.seek(file.size());
        stream << "\n";
    }

    QString balance = "0";
    stream << login << "," << password << "," << accountType << "," << balance;
    file.close();
}


