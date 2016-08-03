//18/06/16
#include "NewProjDialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QFont>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <iostream>

NewProjDialog::NewProjDialog(const std::weak_ptr<Session> session,  QWidget *parent) : QDialog(parent)
{
    this->session = session; // this should be on top so that session can be accessed in setupErrors

    setupUI();

    setupConnections();

    setupErrors();
}

std::weak_ptr<Session> NewProjDialog::getSession(){
    return session;
}


void NewProjDialog::setupUI(){
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // removes the help icon

    nameLabel = new QLabel(tr("Name: "));
    dirLabel = new QLabel(tr("Directory: "));
    statusLabel = new QLabel("");
    pathLabel = new QLabel("");
    nameField = new QLineEdit;
    dirField = new QLineEdit;
    statusFrame = new QFrame;
    browseButton = new QPushButton(tr("Browse..."));
    cancelButton = new QPushButton(tr("Cancel"));
    okButton = new QPushButton(tr("Ok"));
    gMainLayout = new QGridLayout;

    gMainLayout->addWidget(nameLabel, 0, 0, 1, 2);
    gMainLayout->addWidget(nameField, 0, 2, 1, 4);
    gMainLayout->addWidget(dirLabel, 1, 0, 1, 2);
    gMainLayout->addWidget(dirField, 1, 2, 1, 3);
    gMainLayout->addWidget(browseButton, 1, 5, 1, 1);
    gMainLayout->addWidget(pathLabel, 2, 0, 1, 6);
    gMainLayout->addWidget(statusFrame, 3, 0, 1, 6);
    gMainLayout->addWidget(statusLabel, 5, 0, 1, 4);
    gMainLayout->addWidget(cancelButton, 5, 4, 1, 1);
    gMainLayout->addWidget(okButton, 5, 5, 1, 1);

    QSizePolicy sp(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QSizePolicy sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    browseButton->setSizePolicy(sp);
    nameField->setSizePolicy(sp2);
    dirField->setSizePolicy(sp2);
    pathLabel->setSizePolicy(sp2);
    statusFrame->setSizePolicy(sp2);

    statusFrame->setMinimumHeight(5);
    statusFrame->setMaximumHeight(5);

    QFont f( "Arial", 8, QFont::Thin, true);
    pathLabel->setFont(f);
    pathLabel->setStyleSheet("color:#8c8c8c;"); // light gray
    statusLabel->setFont(f);
    statusLabel->setStyleSheet("color:#e3143b;"); // light red

    okButton->setDefault(true); // is pressed when the user presses space or enter keys


//    setWindowFlags(Qt::FramelessWindowHint); // this is horrific!
    setLayout(gMainLayout);
    setWindowTitle(tr("New Project"));
    resize(445, 160);
}

void NewProjDialog::setupConnections(){
    connect(nameField, SIGNAL(textEdited(QString)), this, SLOT(updateProjName(QString)));
    connect(dirField, SIGNAL(textEdited(QString)), this, SLOT(updateProjDir(QString)));
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(saveProject()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(browseButton, SIGNAL(clicked(bool)), this, SLOT(launchFileExplorer()));
}

void NewProjDialog::setupErrors(){
    errorList[0] = tr("Can't Find Directory!");
    errorList[1] = tr("Folder Already Exists!");
    errorList[2] = tr("Invalid Filename!");
    errorList[3] = tr("");
    errorList[4] = tr("");

    // SETTING DEFAULT PROJECT DIR
    try{
        std::shared_ptr<Session> tmpSession = session.lock();
        projDir = tmpSession->lastCreatedProjDir;
    }
    catch (std::bad_weak_ptr b){ // actually this exception will never be thrown
        /// LOG ERROR
        qDebug() << tr("Session Has Expired!");
    }
    projName = "";
    projPath = QString("%1/%2").arg(projDir).arg(projName);
    pathLabel->setText(projPath);
    dirField->setText(projDir);

    QDir dir(projDir);
    // checking if default directory exists
    if(!dir.exists()){
       addError(0);
    }
    addError(2); // projName is currently empty and therefore invalid.

    showStatus();
}


/* sets specified error in errorFlag */
void NewProjDialog::addError(const unsigned int errorCode){
    errorFlag.set(errorCode, true);
}

/* unsets specified error in errorFlag */
void NewProjDialog::removeError(const unsigned int errorCode){
    errorFlag.set(errorCode, false);
}

bool NewProjDialog::hasError(){
    for(int i = 0; i < errorCount; i++){
        if(errorFlag.test(i)){ // test returns true if the error bit is set
            return true;
        }
    }
    return false;
}


/* checks if there is an error and shows the status */
void NewProjDialog::showStatus(){
    bool hasError = false;
    QString str = "";
    for(int i = 0; i < errorCount; i++){
        if(errorFlag.test(i)){ // test returns true if the error bit is set
            str.append(errorList[i] + "  ");
            hasError = true;
        }
    }
    statusLabel->setText(str);
    if(hasError){
        statusFrame->setStyleSheet("background-color:#e3143b;"); // light red
    }
    else{

        statusFrame->setStyleSheet("background-color:#00d32d;"); // light green
    }
}

/* this is called whenever the user types into the nameField */
void NewProjDialog::updateProjName(const QString projName){
    // setting projName and projPath first so that even when there is an error they still hold the last inputted values.
    this->projName = projName;
    projPath = QString("%1/%2").arg(projDir).arg(this->projName);
    pathLabel->setText(projPath);

    // checking if specified projName contains a non-file character; show error if it does.
    bool hasFilenameError = false;
    if(projName.isEmpty()){
        hasFilenameError = true;
    }
    else{
        for(int i = 0; i < projName.length(); i++){
            if(
                    projName.at(i) == '/' ||
                    projName.at(i) == '\\' ||
                    projName.at(i) == '*' ||
                    projName.at(i) == '\"' ||
                    projName.at(i) == '<' ||
                    projName.at(i) == '>' ||
                    projName.at(i) == '?' ||
                    projName.at(i) == '|'
                    ){
                hasFilenameError = true;
                break;
            }
        }
    }
    if(hasFilenameError){
        addError(2);
    }
    else{
        removeError(2);
    }

    // checking if specified directory (projdir) actually exists
    QDir dir(projDir);
    if(!dir.exists()){
        addError(0);
    }
    else{
        removeError(0);
    }

    // checking if folder (projPath) already exist in specified directory
    QDir path(projPath);
    // if projName is "" (empty string)
    // projPath folder will always exist when the user changes the direcory
    // because projPath will be the same as projDir
    // so we must check if projName is empty
    if(!(projName == "") && path.exists()){
        addError(1);
    }
    else{
        removeError(1);
    }

    showStatus();
}

/* updateProjName and updateProjDir have similar implementations
 * but the the arguments taken by each is different and must be stored
 * in different areas (projName and projDir)
*/
void NewProjDialog::updateProjDir(const QString projDir){
    // setting projName and projPath first so that even when there is an error they still hold the last inputted values.
    this->projDir = projDir;
    projPath = QString("%1/%2").arg(this->projDir).arg(projName);
    pathLabel->setText(projPath);

    // checking if specified projName contains a non-file character; show error if it does.
    bool hasFilenameError = false;
    if(projName.isEmpty()){
        hasFilenameError = true;
    }
    else{
        for(int i = 0; i < projName.length(); i++){
            if(
                    projName.at(i) == '/' ||
                    projName.at(i) == '\\' ||
                    projName.at(i) == '*' ||
                    projName.at(i) == '\"' ||
                    projName.at(i) == '<' ||
                    projName.at(i) == '>' ||
                    projName.at(i) == '?' ||
                    projName.at(i) == '|'
                    ){
                hasFilenameError = true;
                break;
            }
        }
    }
    if(hasFilenameError){
        addError(2);
    }
    else{
        removeError(2);
    }

    // checking if specified directory (projdir) actually exists
    QDir dir(projDir);
    if(!dir.exists()){
        addError(0);
    }
    else{
        removeError(0);
    }

    // checking if folder (projPath) already exist in specified directory
    QDir path(projPath);
    // if projName is "" (empty string)
    // projPath folder will always exist when the user changes the direcory
    // because projPath will be the same as projDir
    // so we must check if projName is empty
    if(!(projName == "") && path.exists()){
        addError(1);
    }
    else{
        removeError(1);
    }

    showStatus();
}

/* launches file explorer in order to choose directory */
void NewProjDialog::launchFileExplorer(){
    QString dir =
            QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory")
                ,projDir
                ,/*QFileDialog::DontUseNativeDialog|*/QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks
                );

    if(!(dir == "")){ // the dialog will return empty string if the user clicks cancel.
        updateProjDir(dir);
        dirField->setText(dir);
    }
}

/* saves project folder and files if there is no error */
void NewProjDialog::saveProject(){
    if(hasError()){
        /// LOG ERROR
       QMessageBox::warning(this,tr("Error!"), tr("There is an error in the project path."));
    }
    else{

        // creating project folder
        QDir dir(projDir);
        dir.mkdir(projName); // If folder already exists, it wont reach this stage

        // creating default project and history files
        QFile projDepluFile(projPath + "/Project.deplu");
        QFile historyDepluFle(projPath + "/History.deplu");

        // checking if we are able to open both files
        if(!(   projDepluFile.open(QFile::WriteOnly|QFile::Text)
             && historyDepluFle.open(QFile::WriteOnly|QFile::Text))){
            /// LOG ERROR
            QMessageBox::warning(this, tr("File Error!"), tr("Cannot create needed files. Steps retracted."));
            dir.rmdir(projName); // delete the created folder
            return;
        }

        QTextStream toProjDepluFile(&projDepluFile);
        QTextStream toHistoryDepluFile(&historyDepluFle);

        std::shared_ptr<Session> tmpSession;
        try{
            tmpSession = session.lock();
            projDir = tmpSession->lastCreatedProjDir;
        }
        catch (std::bad_weak_ptr b){
            /// LOG ERROR
            qDebug() << tr("Session Has Expired!");
            QMessageBox::warning(this, tr("Session Error!"), tr("This is quite unfortunate."));
            dir.rmdir(projName); // delete the created folder
            return;
        }

        QString depluHeader =
                "deplu:"
                "\n    version: 001"
                "\n    extra: _"
                "\n..";

        toProjDepluFile <<
                depluHeader +
                "\nproperties:"
                "\n    type: 'project'"
                "\n    name: _"
                "\n    hash:" + tmpSession->getHash(10) +
                "\n    crudeVersion:" + tmpSession->getVersion() +
                "\n    dateCreated: " + tmpSession->getDate() +
                "\n    dateModified: " + tmpSession->getDate() +
                "\n    extra: _"
                "\n.."
                "\nfiles:"
                "\n    groups: name, path, extension, extra [_]"
                "\n    models: name, path, extension, extra [_]"
                "\n    meshFrames: name, path, extension, extra [_]"
                "\n    skeletons: name, path, extension, extra [_]"
                "\n    skins: name, path, extension, extra [_]"
                "\n    animations: name, path, extension, extra [_]"
                "\n    extra: _"
                "\n.."
                "\nfolders:"
                "\n    models: name, path, extension, extra [_]"
                "\n    images: name, path, extension, extra [_]"
                "\n    skeletons: name, path, extension, extra [_]"
                "\n    versions: name, path, extension, extra [_]"
                "\n    extra: _"
                "\n..";

        toHistoryDepluFile <<
                depluHeader +
                "\nproperties:"
                "\n    type: 'history'"
                "\n    name: _"
                "\n    hash:" + tmpSession->getHash(10) +
                "\n    crudeVersion:" + tmpSession->getVersion() +
                "\n    dateCreated: " + tmpSession->getDate() +
                "\n    dateModified: " + tmpSession->getDate() +
                "\n    extra: _"
                "\n.."
                "\nlog: index, used, type, details, date, extra [_]";

        // creating versions subfolder
        QDir dir2(projPath);
        if(!(dir2.mkdir("Versions"))){
            /// LOG ERROR
            QMessageBox::warning(this, tr("Project Error!"), tr("Cannot create needed subfolders. Steps retracted."));
            dir.rmdir(projName); // delete the created folder
            return;
        }

        /// emit openProject signal

        close(); // close the dialog
    }
}
