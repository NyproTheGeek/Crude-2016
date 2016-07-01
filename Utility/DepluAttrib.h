#ifndef DEPLUATTRIB_H
#define DEPLUATTRIB_H

#include <memory>
#include <QObject>
#include <QString>
#include "DepluClass.h"

using namespace std;

class DepluAttrib : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit DepluAttrib(QString name, QObject *parent = 0);

    // CONTENT MANAGEMENT
    void putAttrib(weak_ptr<DepluAttrib> depluAttrib); // single
    void putAttrib(weak_ptr<DepluAttrib> &&depluAttrib); // single
    void putClass(weak_ptr<DepluClass> depluClass); // single
    void putClass(weak_ptr<DepluClass> &&depluClass); // single
    void setTemplate(weak_ptr<DepluClass> depluClass); // to set titles // array
    void setTemplate(weak_ptr<DepluClass> &&depluClass); // to set titles // array
    void addClass(weak_ptr<DepluClass> &&depluClass); // array
    void insertAt(); // array
    void removeAt(); // array
    void clear();

    // ITERATORS
    unsigned int iter;
    bool setIter(unsigned int index);
    bool hasNext();

    // PROPERTIES
    QString name;
    unsigned int size;
    bool array;

    // CHECKS
    bool isBool();
    bool isString();
    bool isFloat();
    bool isDouble();
    bool isInt();
    bool isLong();
    bool isNull();
    bool isEmpty();
    bool isArray();

    // ACCESS
    QString operator[](const unsigned int index);
    bool getBool();
    QString getString();
    float getFloat();
    double getDouble();
    int getInt();
    long getLong();
    void* getNull();

private:
    // CONTENT
    shared_ptr<DepluClass> parent;
    QString value;
    QMap<int, QString> valueArray;

signals:

public slots:
};

#endif // DEPLUATTRIB_H
