#ifndef DEPLUCLASS_H
#define DEPLUCLASS_H

#include <memory>
#include <utility>
#include <QObject>
#include <QString>
#include <QHash>
#include <QMap>
using namespace std;

class DepluClass : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit DepluClass(QObject *parent = 0);

    // PROPERTIES
    QString name;

    // CHECKS
    bool has(QString member);
    bool isBool(QString member);
    bool isString(QString member);
    bool isFloat(QString member);
    bool isDouble(QString member);
    bool isInt(QString member);
    bool isLong(QString member);
    bool isNull(QString member);
    bool isEmpty(QString member);
    bool isArray(QString member);

    // ACCESS
    weak_ptr<DepluClass> getObject(QString member);
    QString getString(QString member);
    float getFloat(QString member);
    double getDouble(QString member);
    int getInt(QString member);
    long getLong(QString member);

    // CONVERT
    QString toString();

private:
    // CONTENT
    shared_ptr<DepluClass> parent;
    /*! use insertMulti()on Maps instead of insert() for
     *  duplicate keys to prevent overwriting!*/
    QMap<QString, pair<QString, int>> attribList; // name-value-index
    QMap<QString, pair<weak_ptr<DepluClass>, int>> classList; // name-object-index

signals:

public slots:
};

#endif // DEPLUCLASS_H
