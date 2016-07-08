//17/06/16
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSplitter>
#include <QHBoxLayout>
#include "SceneView.h"
#include "DopeSheet.h"
#include "ModelView.h"
#include "ModelListView.h"
#include "NewProjDialog.h"

MainWindow::MainWindow(const std::weak_ptr<Session> session, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->session = session;
    setupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::weak_ptr<Session> MainWindow::getSession(){
    return session;
}

void MainWindow::setupUI(){
    ui->setupUi(this);

    sceneView = new SceneView;
    dopeSheet = new DopeSheet;
    modelView = new ModelView;
    modelListView = new ModelListView;
    split1 = new QSplitter; // splits the SceneView and the DopeSheet
    split2 = new QSplitter; // splits the ModelView and the ModelListView
    split3 = new QSplitter;// splits the two splitters
    hLay1 = new QHBoxLayout; // the centralWidget layout

    split1->setOrientation(Qt::Vertical);
    split1->setHandleWidth(15);
    split2->setOrientation(Qt::Vertical);
    split2->setHandleWidth(15);
    split3->setOrientation(Qt::Horizontal); // present for clean code sake
    split3->setHandleWidth(15);

    split1->addWidget(sceneView);
    split1->addWidget(dopeSheet);
    split1->setStretchFactor(0, 4);
    split1->setStretchFactor(1, 1);

    split2->addWidget(modelView);
    split2->addWidget(modelListView);
    split2->setStretchFactor(0, 3);
    split2->setStretchFactor(1, 1);

    split3->addWidget(split1);
    split3->addWidget(split2);

    QList<int> sizes;
    sizes.append(400);
    sizes.append(100);
    split3->setSizes(sizes);

    hLay1->addWidget(split3);

    ui->centralWidget->setLayout(hLay1);
}


void MainWindow::on_actionNew_Project_triggered(){
    NewProjDialog *dialog = new NewProjDialog(session, this);
    dialog->setModal(true);
    dialog->show();
}
