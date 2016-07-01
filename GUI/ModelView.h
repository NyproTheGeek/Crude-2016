//17/06/16
#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QWidget>
class QVBoxLayout;
class QHBoxLayout;
class QTreeView;
class QLabel;
class QFrame;

class ModelView : public QWidget
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit ModelView(QWidget *parent = 0);

private:
    // SETUP
    void setupUI();
//    void setupConnections();

    // UI
    QVBoxLayout *vMainLayout;
    QVBoxLayout *vBodyLayout;
    QHBoxLayout *hTitleLayout;
    QFrame *titleFrame;
    QLabel *titleLabel;
    QTreeView *modelTree;

signals:

public slots:
};

#endif // MODELVIEW_H
