//17/06/16
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Session.h"
#include <QMainWindow>
#include <memory>
class QSplitter;
class QHBoxLayout;
class SceneView;
class DopeSheet;
class ModelView;
class ModelListView;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const std::weak_ptr<Session> session, QWidget *parent = 0);
    ~MainWindow();

    // SESSION FUNCTIONS
    std::weak_ptr<Session> getSession();

private slots:
    void on_actionNew_Project_triggered();

private:
    Ui::MainWindow *ui;

    // SESSION INIT
    std::weak_ptr<Session> session;


    QSplitter *split1;
    QSplitter *split2;
    QSplitter *split3;

    QHBoxLayout *hLay1;

    SceneView *sceneView;
    DopeSheet *dopeSheet;
    ModelView *modelView;
    ModelListView *modelListView;

    // UI FUNCTIONS
    void setupUI();


//    QDialog *newProjectDialog;
};

#endif // MAINWINDOW_H
