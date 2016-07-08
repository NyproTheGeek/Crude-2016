#ifndef DEPLUCLASS_H
#define DEPLUCLASS_H

#include "DepluAttrib.h"
#include "Deplu.h"
#include <QObject>
#include <QString>
#include <QMap>
#include <QPair>
#include <memory>
class DepluArray;

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
class DepluClass : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit DepluClass(QString name, QObject *parent = 0);

    // CONTENT MANAGEMENT
    bool parse(QString& depluStr);
    void parse(QString&& depluStr);
    void clear();
    void remove(const unsigned int index);
    /** attrib **/
    void add(QString name, QString value);
    void add(QString name, int value);
    void add(QString name, long value);
    void add(QString name, float value);
    void add(QString name, double value);
    void add(QString name, bool value);
    void add(QString name, DepluValue value); // For null and empty
    void insert(QString name, QString value, const unsigned int index);
    void insert(QString name, int value, const unsigned int index);
    void insert(QString name, long value, const unsigned int index);
    void insert(QString name, float value, const unsigned int index);
    void insert(QString name, double value, const unsigned int index);
    void insert(QString name, bool value, const unsigned int index);
    void insert(QString name, DepluValue value, const unsigned int index); // For null and empty
    /** class **/
    void add(QString name, std::weak_ptr<DepluClass> depluClass);
    void insert(QString name, std::weak_ptr<DepluClass> depluClass, const unsigned int index);
    /** array **/
    void add(QString name, std::weak_ptr<DepluArray> array);
    void insert(QString name, std::weak_ptr<DepluArray> array, const unsigned int index);

    // PROPERTIES
    static const DepluType type = DepluType::Class;
    unsigned int size; // Number of members

    // ITERATORS
    unsigned int iter;
    bool setIter(unsigned int index);
    bool hasNext();

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
    bool isAttrib(QString member);
    bool isClass(QString member);
    bool isArray(QString member);

    // ACCESS
    std::weak_ptr<DepluClass> getClass(QString member);
    std::weak_ptr<DepluArray> getArray(QString member);
    QString getString(QString member);
    float getFloat(QString member);
    double getDouble(QString member);
    int getInt(QString member);
    long getLong(QString member);
//    DepluValue getNull(QString member);
//    DepluValue getEmpty(QString member);

    // CONVERT
    QString toString();

private:
    // CONTENT
    std::weak_ptr<DepluClass> parent;
    /*! use insertMulti() on Maps instead of insert() for
     *  duplicate keys to prevent overwriting!*/
    QMap<QString, QPair<DepluAttrib, int>> attribList; // name-value-index
    QMap<QString, QPair<std::shared_ptr<DepluClass>, int>> classList; // name-object-index
    QMap<QString, QPair<std::shared_ptr<DepluArray>, int>> arrayList; // name-object-index

signals:

public slots:
};

#endif // DEPLUCLASS_H
