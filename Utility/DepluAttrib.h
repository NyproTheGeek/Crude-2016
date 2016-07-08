#ifndef DEPLUATTRIB_H
#define DEPLUATTRIB_H

#include "Deplu.h"
#include <QObject>

// classes contains objects
// attrib contains values
// objects can either be an attrib or another class
// class->object
// class->[class, attrib->value]
class DepluAttrib : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit DepluAttrib(QObject *parent = 0);

    // CONTENT MANAGEMENT
    void set(QString value);
    void set(int value);
    void set(long value);
    void set(float value);
    void set(double value);
    void set(bool value);
    void set(DepluValue value);

    // PROPERTIES...
    static const DepluType type = DepluType::Attrib;

    // CHECKS
    bool isBool();
    bool isString();
    bool isFloat();
    bool isDouble();
    bool isInt();
    bool isLong();
    bool isNull();
    bool isEmpty();

    // ACCESS
    QString getString();
    float getFloat();
    double getDouble();
    int getInt();
    long getLong();
//    DepluValue getNull();
//    DepluValue getEmpty();

private:
    // PROPERTIES...
    QString value;

signals:

public slots:
};

#endif // DEPLUATTRIB_H
