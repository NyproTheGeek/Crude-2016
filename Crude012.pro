#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T19:06:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Crude012
TEMPLATE = app


SOURCES += main.cpp\
    Core/Group.cpp \
    Core/Model.cpp \
    Core/Skeleton.cpp \
    Core/Bone.cpp \
    Core/SpriteSlot.cpp \
    Core/Sprite.cpp \
    Core/ImageData.cpp \
    Core/TextureAtlas.cpp \
    Core/Mesh.cpp \
    Core/AbstractMesh.cpp \
    Core/MeshFrame.cpp \
    Core/Skin.cpp \
    GUI/DopeSheet.cpp \
    GUI/MainWindow.cpp \
    GUI/ModelListView.cpp \
    GUI/ModelView.cpp \
    GUI/NewProjDialog.cpp \
    GUI/SceneView.cpp \
    Session.cpp \
    Utility/DepluArray.cpp \
    Utility/DepluClass.cpp \
    Utility/DepluAttrib.cpp \
    Exception/DepluException.cpp

HEADERS  += \
    Core/Group.h \
    Core/Model.h \
    Core/Skeleton.h \
    Core/Bone.h \
    Core/SpriteSlot.h \
    Core/Sprite.h \
    Core/ImageData.h \
    Core/TextureAtlas.h \
    Core/Mesh.h \
    Core/AbstractMesh.h \
    Core/MeshFrame.h \
    Core/Skin.h \
    GUI/DopeSheet.h \
    GUI/MainWindow.h \
    GUI/ModelListView.h \
    GUI/ModelView.h \
    GUI/NewProjDialog.h \
    GUI/SceneView.h \
    Session.h \
    Utility/Deplu.h \
    Utility/DepluArray.h \
    Utility/DepluClass.h \
    Utility/DepluAttrib.h \
    Exception/DepluException.h

FORMS    += \
    GUI/MainWindow.ui \
    GUI/NewProjDialog.ui

RESOURCES += Theme/DarkStyle/style.qrc

INCLUDEPATH += C:/Users/Nypro/Documents/Crude012
