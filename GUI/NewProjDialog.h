//18/06/16
#ifndef NEWPROJDIALOG_H
#define NEWPROJDIALOG_H

#include "Session.h"
#include <QDialog>
#include <QDir>
#include <bitset>
#include <memory>
class QLabel;
class QLineEdit;
class QFrame;
class QPushButton;
class QGridLayout;
class QString;

class NewProjDialog : public QDialog
{
    Q_OBJECT
public:
    // CONSTRUCTORS
    explicit NewProjDialog(std::weak_ptr<Session> session, QWidget *parent = 0);

    // SESSION FUNCTIONS
    std::weak_ptr<Session> getSession();

private:

    // SETUP
    std::weak_ptr<Session> session; // be careful, dont set to null bcos of getSession()
    void setupUI();
    void setupConnections();
    void setupErrors();

    // UI
    QLabel *nameLabel;
    QLabel *dirLabel;
    QLabel *statusLabel;
    QLabel *pathLabel;
    QLineEdit *nameField;
    QLineEdit *dirField;
    QFrame *statusFrame;
    QPushButton *browseButton; // might be placed with a older icon in the future
    QPushButton *cancelButton;
    QPushButton *okButton;
    QGridLayout *gMainLayout;

    // PROJECT DETAILS
    QString projName;
    QString projDir;
    QString projPath;

    // ERROR
    static const int errorCount = 5;
    std::bitset<errorCount> errorFlag;
    QString errorList [errorCount];
    void showStatus();
    bool hasError();
    void addError(const unsigned int errorCode);
    void removeError(const unsigned int errorCode);

private slots:
    void launchFileExplorer();
    void saveProject();
    void updateProjName(const QString projName);
    void updateProjDir(const QString projDir);
};

#endif // NEWPROJDIALOG_H
