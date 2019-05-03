#ifndef INFO_H
#define INFO_H

#include <QString>

#include "utils.h"


class Log
{
private:
    Log();

public:
    static QString Info(QString);
    static QString Info(QString, QString);
    static QString Error(QString);
    static QString Error(QString, QString);
};

#endif // INFO_H
