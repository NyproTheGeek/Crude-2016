//27/06/16
#include "Session.h"
//#include <QStringBuilder>
#include <QDebug>
#include <QJsonArray>
//#include <QCryptographicHash>

#include <QDateTime>

Session::Session(QObject *parent) : QObject(parent)
{
    lastCreatedProjDir = "C:/Users/Public/Public Folder/Crude Projects"; /// TODO // get from file instead
    lastCreatedProj = "BluBlaBla"; /// TODO // get from file instead
    jsonFilesInit();
}

QString Session::getDate(){
    QDate currDate = QDate::currentDate();
    return currDate.toString("dd")
            + "/" + currDate.toString("MM")
            + "/" + currDate.toString("yyyy");
}

QString Session::getHash(int extraSeed){
    QString hashSymbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "abcdefghijklmnopqrstuvwxyz"
                          "0123456789";
    // hash = 'CG'
    //        + [15 rand numbers between 0-61]
    //        + [year] + [month] + [day]
    //        + [hour] + [minute] + [second];
    // using the returned number as the index
    // those in braces are replaced with character
    // from hashSymbols

    QString hash = "CG";

    int indexSum = 0;
    int randSum = 0;
    int timeNow = QDateTime::currentDateTime().toTime_t();

    qsrand(timeNow);
    // making the random more random
    // by using the letters in lastCreatedProj
    // and summing up their index position in hashSymbols
    // if such letter is not in hashSymbols
    // a randomly chosen number is deducted from the sum. :)
    // also adding up prng whenever the letter matches
    for(auto letter : lastCreatedProj){
        bool found = false;
        for(int hashSymbolIndex = 0; hashSymbolIndex < hashSymbols.length(); hashSymbolIndex++){
            if(letter == hashSymbols.at(hashSymbolIndex)){
                indexSum += hashSymbolIndex;
                found = true;
                randSum += qrand() % hashSymbolIndex;
            }
        }
        if(!found){
            indexSum -= qrand() % 62;
        }
    }

    qsrand(indexSum + timeNow * extraSeed);
    for(int i = 0; i < 3; i++){
        hash.append(hashSymbols.at(qrand() % 62));
    }

    qsrand(randSum + timeNow  * extraSeed);
    for(int i = 0; i < 4; i++){
        hash.append(hashSymbols.at(qrand() % 62));
    }

    qsrand(timeNow * extraSeed);
    for(int i = 0; i < 8 ; i++){
        hash.append(hashSymbols.at(qrand() % 62));
    }

    // This part is not really useful
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int now[6];
    now[0] = currentDateTime.toString("yy").toInt();
    now[1] = currentDateTime.toString("MM").toInt();
    now[2] = currentDateTime.toString("dd").toInt();
    now[3] = currentDateTime.toString("hh").toInt();
    now[4] = currentDateTime.toString("mm").toInt();
    now[5] = currentDateTime.toString("ss").toInt();
    for(int i = 0; i < 6; i++){
        hash.append(hashSymbols.at(now[i]));
    }
    return hash;
}

QString Session::getVersion(){
    return "'2016.0.1'";
}

void Session::jsonFilesInit(){
    QString hash = getHash(1);

    // DEFAULT HEADER JSON
    QJsonObject propertiesObj;
    propertiesObj["type"] = ""; // TO BE FILLED ON PROJECT CREATION
    propertiesObj["crudeVersion"] = 2016001;
    propertiesObj["hash"] = hash;
    propertiesObj["dateCreated"] = getDate();
    propertiesObj["dateModified"] = getDate();
    propertiesObj["extra"] = QJsonValue::Null;
    defaultHeaderJson["properties"] = propertiesObj;

    // DEFAULT PROJECT JSON
    defaultProjJson["properties"] = propertiesObj;
    QJsonArray foldersArr; // TO BE FILLED ON PROJECT CREATION
    defaultProjJson["folders"] = foldersArr;
    defaultProjJson["projectPath"] = ""; // TO BE FILLED ON PROJECT CREATION
    defaultProjJson["extra"] = QJsonValue::Null;

//    /*! Tests */
//    QJsonObject prop;
//    prop = defaultHeaderJson["properties"].toObject();
//    qDebug() << propertiesObj["type"].toString();
//    qDebug() << QString::number(propertiesObj["crudeVersion"].toInt());
//    qDebug() << propertiesObj["hash"].toString();
//    qDebug() << propertiesObj["dateCreated"].toString();
//    qDebug() << propertiesObj["dateModified"].toString();
//    if (propertiesObj["extra"] == QJsonValue::Null){
//        qDebug() << "extra is Null" ;
//    }
//    /*! Tests */

    // DEFAULT HISTORY JSON
    defaultHistoryJson["properties"] = propertiesObj;
    QJsonArray logArr; // TO BE FILLED ON PROJECT CREATION
    defaultHistoryJson["folders"] = logArr;
    defaultHistoryJson["projectPath"] = ""; // TO BE FILLED ON PROJECT CREATION
    defaultHistoryJson["extra"] = QJsonValue::Null;

    // DEFAULT GROUPS JSON
    defaultGroupsJson["properties"] = propertiesObj;
    QJsonArray modelGroupsArr; // TO BE FILLED ON PROJECT CREATION
    defaultGroupsJson["folders"] = modelGroupsArr;
    defaultGroupsJson["projectPath"] = ""; // TO BE FILLED ON PROJECT CREATION
    defaultGroupsJson["extra"] = QJsonValue::Null;

    // DEFAULT MODELS JSON
    defaultModelsJson["properties"] = propertiesObj;
    QJsonArray models; // TO BE FILLED ON PROJECT CREATION
    defaultModelsJson["folders"] = models;
    defaultModelsJson["projectPath"] = ""; // TO BE FILLED ON PROJECT CREATION
    defaultModelsJson["extra"] = QJsonValue::Null;
}
