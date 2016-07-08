#ifndef DEPLUARRAY_H
#define DEPLUARRAY_H

#include "Deplu.h"
#include "DepluClass.h"
#include <QMap>
#include <QObject>
#include <memory>

/*!
 * User should beware of cyclic inclusion, where a class/array class contains
 * reference to another class/array class, and then the referenced class/array class also contains reference
 * to the class/array class.
 * If toString() were to be called in such cases, the string output
 * will be endless. Other things can go wrong too.
 * I'm going to look at a way of catching this.
 * 04/07/16 I came up with a solution, which is to compare ancestors reference
 * with the reference of the class/array class being added.
 * If they are the same, then there is a circular ref/inclusion.
 * And because this sarch can potentially be deep, an depu entity can only have one parent.
*/
// Classes contains objects
// Attrib contains values
// Objects can either be an attrib or another class
// Class->Object
// Class->[Class, Attrib->Value]
// An array can either be an array attrib or an array class
// Array Attribs hold array of values
// Array Classes hold array of objects
// This class can be used to store either array attrib or array class
class DepluArray : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit DepluArray(QObject *parent = 0);

    // CONTENT MANAGEMENT
    void clear();
    void remove(const unsigned int index);
    /** Array Attrib **/
    void add(QString value);
    void add(int value);
    void add(long value);
    void add(float value);
    void add(double value);
    void add(bool value);
    void add(DepluValue value); // For null and empty
    void insert(QString value, const unsigned int index);
    void insert(int value, const unsigned int index);
    void insert(long value, const unsigned int index);
    void insert(float value, const unsigned int index);
    void insert(double value, const unsigned int index);
    void insert(bool value, const unsigned int index);
    void insert(DepluValue value, const unsigned int index);  // For null and empty
    /** Array Class **/
    void setTemplate(std::weak_ptr<DepluClass> object);
    void add(std::weak_ptr<DepluClass> object);
    void insert(std::weak_ptr<DepluClass> object, const unsigned int index);

    // PROPERTIES
    DepluType type; // Array Attrib or Array Class
    unsigned int size;

    // ITERATORS
    unsigned int iter;
    bool setIter(unsigned int index);
    bool hasNext();

    // CHECKS
    bool isAttribArray(QString member);
    bool isClassArray(QString member);

    // ACCESS
    std::weak_ptr<DepluClass> operator[](const unsigned int index);

private:
    // CONTENT
    std::weak_ptr<DepluClass> parent;
    QMap<int, QString> valueList; // Array Attrib
    QMap<int, std::shared_ptr<DepluClass>> objectList; // Array Class

signals:

public slots:
};

#endif // DEPLUARRAY_H
