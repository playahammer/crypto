#include "log.h"


Log::Log(){

}


QString Log::Info(QString s){
   QString s1 = QString("[Info] %1 : %2\n").arg(Utils::getCurrentStringTime(), s);
   return s1;
}

QString Log::Info(QString s1, QString s2){
    return QString("[Info] %1 : %2 %3\n").arg(Utils::getCurrentStringTime(), s1, s2);
}
QString Log::Error(QString s){
    QString s1 = QString("[Error] %1 : %2\n").arg(Utils::getCurrentStringTime(), s);
    return s1;
}

QString Log::Error(QString s1, QString s2){
    return QString("[Error] %1 : %2 %3\n").arg(Utils::getCurrentStringTime(), s1, s2);
}
