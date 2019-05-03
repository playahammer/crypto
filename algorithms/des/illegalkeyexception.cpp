#include "illegalkeyexception.h"

IllegalKeyException::IllegalKeyException(QString key, QString errMsg)
{
    this->err = new QString();
    this->err->append("Error: ");
    this->err->append(key);
    this->err->append(": ");
    this->err->append(errMsg);
}

IllegalKeyException::~IllegalKeyException(){
    //delete this->err;
}
