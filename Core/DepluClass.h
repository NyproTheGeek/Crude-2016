#ifndef DEPLUCLASS_H
#define DEPLUCLASS_H

#include <QObject>

class DepluClass : public QObject
{
    Q_OBJECT
public:
    explicit DepluClass(QString name, QObject *parent = 0);

    // MANAGEMENT
    void put(QString name);

    // CONTENT MANAGEMENT
    void parse(QString&& depluString);
    void clean();

    // ITERATORS
    bool setIter(int);
    bool hasNext();

    // PROPERTIES
    int size;

    // CHECKS
    bool isAClass; // isAnAttrib otherwise
    bool has(QString member); // used to know if it contains a member
    bool isBool();
    bool isString();
    bool isFloat();
    bool isDouble();
    bool isInt();
    bool isLong();
    bool isNull();
    bool isEmpty();
    bool isArray();
    bool isClass();
    bool isAttrib();
    bool isBool(QString member);
    bool isString(QString member);
    bool isFloat(QString member);
    bool isDouble(QString member);
    bool isInt(QString member);
    bool isLong(QString member);
    bool isNull(QString member);
    bool isEmpty(QString member);

    // ACCESS
    weak_ptr<DepluEntity> operator[](int index);
    bool getBool();
    QString getString();
    float getFloat();
    double getDouble();
    int getInt();
    long getLong();
    void* getNull();
    QString getString(QString member);
    float getFloat(QString member);
    double getDouble(QString member);
    int getInt(QString member);
    long getLong(QString member);

private:
    // CONTENT
    shared_ptr<DepluEntity> root;
    QList<shared_ptr<DepluEntity>> entityList;

signals:

public slots:
};

#endif // DEPLUCLASS_H
