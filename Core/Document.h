//29/06/16
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <memory>
#include <QObject>
#include <QList>
#include "DepluObject.h"
class QString;

using namespace std;

// A Document is has a root Deplu Object.
// In Deplu, an object is different from a value.
// A object either contains an array of values or an array of objects
// not both.
class Document : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit Document(QObject *parent = 0);

    // CONTENT MANAGEMENT
    void parse(QString&& depluString);
    void clean();

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
    shared_ptr<DepluObject> root;
    QList<shared_ptr<DepluObject>> objectList;

signals:

public slots:
};

#endif // DOCUMENT_H
