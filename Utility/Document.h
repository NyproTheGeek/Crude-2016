//29/06/16
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <memory>
#include <QObject>
#include <QList>
#include "DepluClass.h"
#include "DepluAttrib.h"
class QString;

using namespace std;


class Document : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit Document(QObject *parent = 0);

private:
    // CONTENT
    shared_ptr<DepluClass> root;
    QList<shared_ptr<DepluClass>> classList;
    QList<shared_ptr<DepluAttrib>> attribList;

signals:

public slots:
};

#endif // DOCUMENT_H
