//29/06/16
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
class QString;
using namespace std;


class Document : public QObject
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit Document(QObject *parent = 0);

signals:

public slots:
};

#endif // DOCUMENT_H
