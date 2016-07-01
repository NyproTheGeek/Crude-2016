#ifndef DEPLUCLASS_H
#define DEPLUCLASS_H

#include <QObject>

class DepluClass : public QObject
{
    Q_OBJECT
public:
    explicit DepluClass(QObject *parent = 0);

signals:

public slots:
};

#endif // DEPLUCLASS_H