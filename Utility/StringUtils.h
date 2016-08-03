#ifndef STRINGUTILS_H
#define STRINGUTILS_H
class QString;
class QStringList;
class QRegularExpression;

class StringUtils{
public:

    static QStringList tokenize(const QString &str, const QString &delimiters, bool keepDelimiters, bool keepWhitespace, bool keepEmptyStrings);
    static QStringList tokenize(const QString &str, const QString &delimitersToKeep, QString &delimitersToSkip);
    // splits string with delimitersToSkip, then resulting tokens are further split with delimitersToKeep
    static QStringList tokenize(QString str, const QRegularExpression &delimitersToSkip, QRegularExpression &delimitersToKeep);
    // splits string with delimitersToKeep, then resulting tokens are further split with delimitersToSkip
    static QStringList flipTokenize(const QString &str, const QRegularExpression &delimitersToKeep, QRegularExpression &delimitersToSkip);
    static QStringList fastTokenize(const QString &str, const QString &delimiters);
};

#endif // STRINGUTILS_H
