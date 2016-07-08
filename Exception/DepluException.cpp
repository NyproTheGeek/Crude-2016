#include "DepluException.h"
#include <QDebug>

DepluException::DepluException(const QString errorMsg, const unsigned int lineIndex, const unsigned int tokenCol)
{
    this->errorMsg = errorMsg;
    this->lineIndex = lineIndex;
    this->tokenCol = tokenCol;
}

void DepluException::printMessage()
{
    qDebug() << errorMsg << " @ Line " << lineIndex << ", Col " << tokenCol;
}
