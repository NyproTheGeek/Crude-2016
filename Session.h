//27/06/16
#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QJsonObject>
#include <QString>

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject *parent = 0);

    QString lastCreatedProjDir; /// TODO

    QString lastCreatedProj; /// TODO

    QJsonObject defaultHeaderJson;

    QJsonObject defaultProjJson;

    QJsonObject defaultHistoryJson;

    QJsonObject defaultGroupsJson;

    QJsonObject defaultModelsJson;

    QJsonObject defaultMeshFramesJson;

    // UTILITIES
    QString getDate();

    QString getHash(int extraSeed);

    QString getVersion();

    void jsonFilesInit();
signals:

public slots:
};

#endif // SESSION_H
