#include "StringUtils.h"
#include <QString>
#include <QStringBuilder>
#include <QRegularExpression>
#include <QDebug>
#include <memory>
using namespace std;

QStringList StringUtils::tokenize(const QString &str, const QString &delimiters, bool keepDelimiters, bool keepWhitespace, bool keepEmptyStrings){
    // default keeps token, skips empty, skips space delimiters
    QStringList strList;
    int lastDelimiterIndex = 0;
    int strLen = str.length();
    for(int index = 0; index < strLen; index++){
        for(auto delim : delimiters){
            if(delim == str.at(index)){
                QString tmp = str.mid(lastDelimiterIndex, index - lastDelimiterIndex);
                if(tmp.isEmpty() && !keepEmptyStrings){
                    if(keepDelimiters){
                        if(delim == ' ' && !keepWhitespace){}
                        else strList << delim;
                    }
                }
                else{
                    strList << std::move(tmp);
                    if(keepDelimiters){
                        if(delim == ' ' && !keepWhitespace){}
                        else strList << delim;
                    }
                }
                lastDelimiterIndex = index + 1;
            }
        }
    }

    if(lastDelimiterIndex < strLen){
        QString tmp = str.mid(lastDelimiterIndex, strLen - lastDelimiterIndex);
        if(!tmp.isEmpty()){
            strList << std::move(tmp);
        }
    }

    return strList;
}

QStringList StringUtils::tokenize(const QString &str, const QString &delimitersToKeep, QString &delimitersToSkip){
    // skips space delimiters
    QStringList strList;
    int lastDelimiterIndex = 0;
    int strLen = str.length();
    bool delimDetermined = false;
    for(int index = 0; index < strLen; index++){
        if(!delimitersToKeep.isNull() && !delimitersToKeep.isEmpty()){
            for(auto delim : delimitersToKeep){
                if(delim == str.at(index)){
                    QString token = std::move(str.mid(lastDelimiterIndex, index - lastDelimiterIndex));
                    if(!token.isEmpty()){
                        strList << std::move(token);
                    }
                    strList << delim;
                    lastDelimiterIndex = index + 1;
                    delimDetermined = true;
                    break;
                }
            }
        }

        if(!delimitersToSkip.isNull() && !delimitersToSkip.isEmpty() && !delimDetermined){
            for(auto delim : delimitersToSkip){
                if(delim == str.at(index)){
                    QString token = std::move(str.mid(lastDelimiterIndex, index - lastDelimiterIndex));
                    if(!token.isEmpty()){
                        strList << std::move(token);
                    }
                    lastDelimiterIndex = index + 1;
                    break;
                }
            }
        }

        delimDetermined = false;
    }

    if(lastDelimiterIndex < strLen){
        QString token = std::move(str.mid(lastDelimiterIndex, strLen - lastDelimiterIndex));
        if(!token.isEmpty()){
            strList << std::move(token);
        }
    }

    return strList;
}
// splits string with delimitersToSkip, then resulting tokens are further split with delimitersToKeep
QStringList StringUtils::tokenize(QString str, const QRegularExpression &delimitersToSkip, QRegularExpression &delimitersToKeep){
    // Note! This function skips empty tokens
    // It uses the enclosing capture group only (capture group zero)

    // Optimizing for JIT enabled compilers.
    // I don't think it even needs optimizing as much
    delimitersToSkip.optimize();
    delimitersToKeep.optimize();

    QRegularExpressionMatch toSkipMatch = std::move(delimitersToSkip.match(str));
    while(toSkipMatch.hasMatch()){
        toSkipMatch = std::move(delimitersToSkip.match(str));
        // Removing deimitersToSkip from string
        str.remove(toSkipMatch.capturedStart(0), toSkipMatch.capturedLength(0));
    }

    QStringList strList; // Stores the tokens that will broken down in str
    int lastCapturedEndIndex = 0;
    QRegularExpressionMatchIterator toKeepMatchIterator = std::move(delimitersToKeep.globalMatch(str));
    while(toKeepMatchIterator.hasNext()){
        QRegularExpressionMatch toKeepMatch = std::move(toKeepMatchIterator.next());
        int capturedStartIndex = toKeepMatch.capturedStart(0);
        int capturedLength = toKeepMatch.capturedLength(0);
        // Collecting delimiter and its preceding token
        QString token = std::move(str.mid(lastCapturedEndIndex, capturedStartIndex - lastCapturedEndIndex));
        QString delim = std::move(str.mid(capturedStartIndex, capturedLength));
        // If token is empty, don't keep. Who keeps empty stuffs anyway?
        if(!token.isEmpty()){
            strList << std::move(token);
        }
        strList << std::move(delim);
        lastCapturedEndIndex = toKeepMatch.capturedEnd(0);
    }

    if(lastCapturedEndIndex < str.length()){
        QString token = std::move(str.mid(lastCapturedEndIndex, str.length() - lastCapturedEndIndex));
        if(!token.isEmpty()){
            strList << std::move(token);
        }
    }

    return strList;
}
// splits string with delimitersToKeep, then resulting tokens are further split with delimitersToSkip
QStringList StringUtils::flipTokenize(const QString &str, const QRegularExpression &delimitersToKeep, QRegularExpression &delimitersToSkip){
    // Note! This function skips empty tokens
    // It uses the enclosing capture group only (capture group zero)

    QStringList strList;
    int lastCapturedEndIndex = 0;

    // Optimizing for JIT enabled compilers.
    // I don't think it even needs optimizing as much
    delimitersToKeep.optimize();
    delimitersToSkip.optimize();

    QRegularExpressionMatchIterator toKeepMatchIterator = std::move(delimitersToKeep.globalMatch(str));
    while(toKeepMatchIterator.hasNext()){
        QRegularExpressionMatch toKeepMatch = std::move(toKeepMatchIterator.next());
        int capturedStartIndex = toKeepMatch.capturedStart(0);
        int capturedLength = toKeepMatch.capturedLength(0);
        // Collecting delimiter and its preceding token
        QString token = std::move(str.mid(lastCapturedEndIndex, capturedStartIndex - lastCapturedEndIndex));
        QString delim = std::move(str.mid(capturedStartIndex, capturedLength));
        // If token is empty, don't keep. Who keeps empty stuffs anyway?
        if(!token.isEmpty()){
            strList << std::move(token);
        }
        strList << std::move(delim);
        lastCapturedEndIndex = toKeepMatch.capturedEnd(0); // So I found out capturedEnd returns an offset(+1) of the match end index
        // I guess capturedEnd was implemented as capturedStart + capturedLength which I does not truly
        // represent the index of the match's final character but a +1 offset from the character's index
    }

    if(lastCapturedEndIndex < str.length()){
        QString token = std::move(str.mid(lastCapturedEndIndex, str.length() - lastCapturedEndIndex));
        if(!token.isEmpty()){
            strList << std::move(token);
        }
    }

    QStringList strList2; // strList is further broken down using delimitersToSkip. The result is stored in strList2
    for(auto str2 : strList){
        lastCapturedEndIndex = 0;
        QRegularExpressionMatchIterator toSkipMatchIterator = std::move(delimitersToSkip.globalMatch(str2));
        while(toSkipMatchIterator.hasNext()){
            QRegularExpressionMatch toSkipMatch = std::move(toSkipMatchIterator.next());
            int capturedStartIndex = toSkipMatch.capturedStart(0);
            // Collecting delimiter's preceding token
            QString token = std::move(str2.mid(lastCapturedEndIndex, capturedStartIndex - lastCapturedEndIndex));
            // If token is empty, don't keep. Who keeps empty stuffs anyway?
            if(!token.isEmpty()){
                strList2 << std::move(token);
            }
            lastCapturedEndIndex = toSkipMatch.capturedEnd(0); // This return an offset from the actual last index
            // It all makes sense to me now. This helps avoid unecessary additions and subtractions.
        }

        if(lastCapturedEndIndex < str2.length()){
            QString token = std::move(str2.mid(lastCapturedEndIndex, str2.length() - lastCapturedEndIndex));
            if(!token.isEmpty()){
                strList2 << std::move(token);
            }
        }
    }


    return strList2;
}

QStringList StringUtils::fastTokenize(const QString &str, const QString &delimiters){
    // This function keeps delimiters and skips empty tokens
    // It also skips space and tab delimiters

    QStringList strList;
    int lastDelimiterIndex = 0;
    int strLen = str.length();
    for(int index = 0; index < strLen; index++){
        for(auto delim : delimiters){
            if(delim == str.at(index)){
                QString token = str.mid(lastDelimiterIndex, index - lastDelimiterIndex);
                if(!token.isEmpty()){
                    strList << std::move(token);
                }
                if(delim != ' ' || delim != '\t') strList << delim;
                lastDelimiterIndex = index + 1;
            }
        }
    }

    if(lastDelimiterIndex < strLen){
        QString token = str.mid(lastDelimiterIndex, strLen - lastDelimiterIndex);
        if(!token.isEmpty()){
            strList << std::move(token);
        }
    }

    return strList;
}
