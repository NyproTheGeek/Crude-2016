//27/06/16
#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject *parent = 0);


    QString lastCreatedProjDir; /// TODO

    QString getDate(); /// TODO

    QString getHash(); /// TODO

signals:

public slots:
};

#endif // Session_H