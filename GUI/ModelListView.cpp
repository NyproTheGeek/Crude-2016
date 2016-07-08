//17/06/16
#include "ModelListView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>
#include <array>


ModelListView::ModelListView(QWidget *parent) : QWidget(parent)
{
    setupUI();
    setupConnections();
}

void ModelListView::setupUI(){
    vMainLayout = new QVBoxLayout;
    hTopLayout = new QHBoxLayout;
    vBodyLayout = new QVBoxLayout;
    hTitleLayout = new QHBoxLayout;
    titleFrame = new QFrame;
    titleLabel = new QLabel(tr("Model List"));
    testField = new QLineEdit; /// FOR TEST PURPOSE ONLY
    newButton = new QPushButton(tr("New"));
    addButton = new QPushButton(tr("Add"));
    modelList = new QListView;


    hTitleLayout->addStretch();
    hTitleLayout->addWidget(titleLabel);
    hTitleLayout->addStretch();

    hTopLayout->addWidget(testField); /// FOR TEST PURPOSE ONLY
    hTopLayout->addWidget(newButton);
    hTopLayout->addWidget(addButton);

    vBodyLayout->addWidget(modelList);

    vMainLayout->addWidget(titleFrame);
    vMainLayout->addLayout(hTopLayout);
    vMainLayout->addLayout(vBodyLayout);

    titleFrame->setLayout(hTitleLayout);
    setLayout(vMainLayout);
}

void ModelListView::setupConnections(){
    connect(newButton, SIGNAL(clicked(bool)), this, SLOT(openMsg())); /// FOR TEST PURPOSE ONLY
}

void ModelListView::openMsg() /// FOR TEST PURPOSE ONLY
{
    std::array<int, 7> myArray= {1, 2, 3, 4};
    for(int i = 0; i < myArray.size(); i++){

        qDebug() << myArray.at(i);
    }
    QMessageBox::information(this,"Information", "QString::number(x)");
}




