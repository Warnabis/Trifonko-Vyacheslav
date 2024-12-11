#ifndef INPUTVALIDATIONEXCEPTION_H
#define INPUTVALIDATIONEXCEPTION_H

#include <exception>
#include <QString>
#include <QRegularExpression>

class InputValidationException : public std::exception {
public:

   explicit InputValidationException(const QString& message)
       : errorMessage(message) {}

   const char* what() const noexcept override {
       return errorMessage.toUtf8().constData();
   }

   static void checkInput(const QString& input);

private:
   QString errorMessage;
};

#endif
