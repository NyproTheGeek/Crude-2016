//17/06/16
#include "GUI/MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
//#include <QPushButton>
#include <memory>
#include "Session.h"

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

    window.resize(960, 600);
    window.show();

    return a.exec();
}
