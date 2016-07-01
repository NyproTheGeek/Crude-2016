//17/06/16
#include "ModelView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeView>
#include <QLabel>
#include <QFrame>

ModelView::ModelView(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void ModelView::setupUI(){
    vMainLayout = new QVBoxLayout;
    vBodyLayout = new QVBoxLayout;
    hTitleLayout = new QHBoxLayout;
    titleFrame = new QFrame;
    titleLabel = new QLabel(tr("Model Tree"));
    modelTree = new QTreeView;

    hTitleLayout->addStretch();
    hTitleLayout->addWidget(titleLabel);
    hTitleLayout->addStretch();

    vBodyLayout->addWidget(modelTree);

    vMainLayout->addWidget(titleFrame);
    vMainLayout->addLayout(vBodyLayout);

    titleFrame->setLayout(hTitleLayout);
    setLayout(vMainLayout);
}
