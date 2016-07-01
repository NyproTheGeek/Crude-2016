//17/06/16
#include "ModelListView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QMessageBox>

ModelListView::ModelListView(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void ModelListView::setupUI(){
    vMainLayout = new QVBoxLayout;
    hTopLayout = new QHBoxLayout;
    vBodyLayout = new QVBoxLayout;
    hTitleLayout = new QHBoxLayout;
    titleFrame = new QFrame;
    titleLabel = new QLabel(tr("Model List"));
    newButton = new QPushButton(tr("New"));
    addButton = new QPushButton(tr("Add"));
    modelList = new QListView;


    hTitleLayout->addStretch();
    hTitleLayout->addWidget(titleLabel);
    hTitleLayout->addStretch();

    hTopLayout->addStretch();
    hTopLayout->addWidget(newButton);
    hTopLayout->addWidget(addButton);

    vBodyLayout->addWidget(modelList);

    vMainLayout->addWidget(titleFrame);
    vMainLayout->addLayout(hTopLayout);
    vMainLayout->addLayout(vBodyLayout);

    titleFrame->setLayout(hTitleLayout);
    setLayout(vMainLayout);
}

//void ModelListView::setupConnections(){
//}




