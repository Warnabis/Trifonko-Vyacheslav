#include "InputValidationException.h"
#include <QRegularExpression>

void InputValidationException::checkInput(const QString& input) {

    QRegularExpression invalidCharsPattern("[^a-zA-Z0-9]");
    if (invalidCharsPattern.match(input).hasMatch()) {
        throw InputValidationException("Недопустимые \nсимволы в вводе.");
    }
}
