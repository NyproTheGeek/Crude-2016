//27/06/16
#ifndef ABSTRACTMESH_H
#define ABSTRACTMESH_H

#include <QObject>

class AbstractMesh : public QObject
{
    Q_OBJECT
public:
    explicit AbstractMesh(QObject *parent = 0);

private:

signals:

public slots:
};

#endif // ABSTRACTMESH_H
