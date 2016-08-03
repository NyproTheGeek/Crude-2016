//17/06/16
#include "Session.h"
#include "GUI/MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
//#include <QStringBuilder>
//#include <QRegularExpression>
#include <QDebug>
#include <QDateTime>
//#include <QCryptographicHash>
//#include <QPushButton>
#include <memory>
#include <iostream>
#include <time.h>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    shared_ptr<Session> session(new Session(nullptr)); // using make_shared has side effects on weak_ptr
    MainWindow window(session);
    window.setWindowTitle("CRUDE 2016.0.1");

    QFile f(":/DarkStyle/style.css");
    if (f.open(QFile::ReadOnly | QFile::Text)){
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    else{
        printf("Cannot Open QSS file\n");
    }


    {
        /*! Tests */
        for(int i = 0; i < 10; i++)
            qDebug() << session->getHash(i);
        /*! Tests */
    }

    window.resize(960, 600);
    window.show();

    return a.exec();
}
