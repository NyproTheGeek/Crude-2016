//29/06/16
#ifndef DEPLUOBJECT_H
#define DEPLUOBJECT_H

#include <memory>
#include <QObject>
#include <QList>
#include "DepluObject.h"
class QString;

using namespace std;

class DepluObject : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit DepluObject(QObject *parent = 0);

    // ITERATORS
    bool setIter(int);
    bool hasNext();

    // CHECKS
    bool has(QString member); // used to know if it contains objects
    bool isBool();
    bool isString();
    bool isFloat();
    bool isDouble();
    bool isInt();
    bool isLong();
    bool isNull();
    bool isEmpty();

    // ACCESS
    weak_ptr<DepluObject> get(); // used to get objects
    weak_ptr<DepluObject> getParent();
    weak_ptr<DepluObject> operator[](int index);
    bool getBool();
    QString getString();
    float getFloat();
    double getDouble();
    int getInt();
    long getLong();
    DepluObject* getNull() { return nullptr; }

private:
    // CONTENT
    weak_ptr<DepluObject> parent;
    QList<weak_ptr<DepluObject>> objectList;


signals:

public slots:
};

#endif // DEPLUOBJECT_H
