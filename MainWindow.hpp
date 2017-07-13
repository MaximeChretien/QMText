#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWidgets>
#include "Editor.hpp"
#include "Tab.hpp"
#include "FindAndReplaceWidget.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString confFile, QFont font, QString lang, QString theme);
    void createMenus();
    void createActions();
    void changeLanguage(QString langue);
    void changeTheme(QString theme);

private slots:
    void about();
    void newFile(QString path = "");
    void open();
    void changeFont();

    void changeWindowTitle();

    void zoomIn();
    void zoomOut();

    void closeEvent(QCloseEvent * event); //save files before quit

    // drag & drop
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

    void changeLanguageSystem();
    void changeLanguageFr();
    void changeLanguageEn();

    void changeThemeLight();
    void changeThemeDark();


private:
    QVBoxLayout *layout;
    Tab *tabWidget;
    FindAndReplaceWidget *findAndReplace;
    QStringList confData; //config data tab
    QMenuBar *mnuBar;

    //actions
    QAction *actionNew;
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionCut;
    QAction *actionOpen;
    QAction *actionFont;
    QAction *actionPrint;
    QAction *actionZoomMore;
    QAction *actionZoomLess;
    QAction *actionFindAndReplace;

    //langues
    QAction *actionLanguageSystem;
    QAction *actionLanguageFr;
    QAction *actionLanguageEn;

    //thèmes
    QAction *actionThemeLight;
    QAction *actionThemeDark;

    QString configFile; //config file path
};

#endif // MainWindow

