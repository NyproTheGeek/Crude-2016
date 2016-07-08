#ifndef DEPLUEXCEPTION_H
#define DEPLUEXCEPTION_H

#include <QString>
#include <exception>

class DepluException : public std::exception
{
public:
    DepluException(const QString errorMsg, const unsigned int lineIndex, const unsigned int tokenCol);

    QString errorMsg;
    unsigned int lineIndex;
    unsigned int tokenCol;

    void printMessage();
    void logMessage();
};

#endif // DEPLUEXCEPTION_H
