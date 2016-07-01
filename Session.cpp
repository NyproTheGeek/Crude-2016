//27/06/16
#include "Session.h"

Session::Session(QObject *parent) : QObject(parent)
{
    lastCreatedProjDir = "C:/Users/Public/Public Folder/Crude Projects"; /// TODO
}


QString Session::getDate(){
    return "<Placeholder>"; /// TODO
}

QString Session::getHash(){
    return "<Placeholder>"; /// TODO
}
