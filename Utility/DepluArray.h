#ifndef DEPLUARRAY_H
#define DEPLUARRAY_H

#include <memory>
#include <QObject>
#include "DepluClass.h"
using namespace std;

// classes contains objects
// attrib contains values
// objects can either be an attrib or another class
// class->object
// class->[class, attrib->value]
// an array can either be an array attrib or an array class
// array attribs hold array of values
// array classes hold array of objects

// This class can be used to store an array attrib or an array class
class DepluArray : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit DepluArray(QObject *parent = 0);

    // CONTENT MANAGEMENT
    void clear();
    void remove(const unsigned int index);
    /** array attrib **/
    void add(QString value);
    void add(QString &&value);
    void add(int value);
    void add(long value);
    void add(float value);
    void add(double value);
    void add(bool value);
    void add(); // empty
    void add(void *value); // null // only nullptr allowed
    void insert(QString value, const unsigned int index);
    void insert(QString &&value, const unsigned int index);
    void insert(int value, const unsigned int index);
    void insert(long value, const unsigned int index);
    void insert(float value, const unsigned int index);
    void insert(double value, const unsigned int index);
    void insert(bool value, const unsigned int index);
    void insert(const unsigned int index); // empty
    void insert(void *value, const unsigned int index); // null // only nullptr allowed
    /** array class **/
    void add(weak_ptr<DepluClass> object);
    void insert(weak_ptr<DepluClass> object, const unsigned int index);

    // ITERATORS
    unsigned int iter;
    bool setIter(unsigned int index);
    bool hasNext();

    // PROPERTIES
    QString name;
    unsigned int size;
    bool arrayClass; // arrayAttrib if false

    // ACCESS
    weak_ptr<DepluClass> operator[](const unsigned int index);

private:
    // CONTENT
    shared_ptr<DepluClass> parent;
    QMap<int, QString> valueList; // array attrib
    QMap<int, weak_ptr<DepluClass>> objectList; // array class

signals:

public slots:
};

#endif // DEPLUARRAY_H
