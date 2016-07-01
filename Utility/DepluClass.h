#ifndef DEPLUCLASS_H
#define DEPLUCLASS_H

#include <memory>
#include <QObject>
#include <QMap>
#include "DepluAttrib.h"

using namespace std;

class DepluClass : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit DepluClass(QString name, QObject *parent = 0);

    // CONTENT MANAGEMENT
    void putAttrib(weak_ptr<DepluAttrib> depluAttrib); // single
    void putAttrib(weak_ptr<DepluAttrib> &&depluAttrib); // single
    void putClass(weak_ptr<DepluClass> depluClass); // single
    void putClass(weak_ptr<DepluClass> &&depluClass); // single
    void setTemplate(weak_ptr<DepluClass> depluClass); // to set titles // array
    void setTemplate(weak_ptr<DepluClass> &&depluClass); // to set titles // array
    void addClass(weak_ptr<DepluClass> &&depluClass); // array
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
    bool has(QString member); // used to know if it contains a member
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
    weak_ptr<DepluClass> operator[](const unsigned int index); // array
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
    QMap<int, shared_ptr<DepluClass>> classList;
    QMap<int, shared_ptr<DepluAttrib>> attribList;
    QMap<int, shared_ptr<DepluClass>> classArray; // seperated for clarity

signals:

public slots:
};

#endif // DEPLUCLASS_H
