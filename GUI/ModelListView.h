//17/06/16
#ifndef MODELLISTVIEW_H
#define MODELLISTVIEW_H

#include <QWidget>
class QVBoxLayout;
class QHBoxLayout;
class QListView;
class QPushButton;
class QLabel;
class QFrame;
class QString;
class QLineEdit;


class ModelListView : public QWidget
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit ModelListView(QWidget *parent = 0);

private:
    // SETUP
    void setupUI();
    void setupConnections();

    // UI
    QVBoxLayout *vMainLayout;
    QHBoxLayout *hTopLayout;
    QVBoxLayout *vBodyLayout;
    QHBoxLayout *hTitleLayout;
    QFrame *titleFrame;
    QLabel *titleLabel;
    QLineEdit *testField; /// FOR TEST PURPOSE ONLY
    QPushButton *newButton;
    QPushButton *addButton;
    QListView *modelList;


signals:

public slots:
    void openMsg(); /// FOR TEST PURPOSE ONLY

};

#endif // MODELLISTVIEW_H
