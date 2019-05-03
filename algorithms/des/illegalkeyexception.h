#ifndef ILLEGALKEYEXCEPTION_H
#define ILLEGALKEYEXCEPTION_H

#include <QString>

#include <iostream>
#include <exception>

using namespace std;

class IllegalKeyException :exception
{
public:
    IllegalKeyException(QString key, QString errMsg);
    const char* what() const noexcept override{
        return err->toUtf8().data();
    }
    ~IllegalKeyException() override;

private:
    QString *err;
};

#endif // ILLEGALKEYEXCEPTION_H
