/*
**  Copyright 2018 - Maxime Chretien (MixLeNain)
**
**  This file is part of QMText.
**
**  QMText is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  any later version.
**
**  QMText is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with QMText.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWidgets>
#include "Editor.hpp"
#include "Tab.hpp"
#include "FindAndReplaceWidget.hpp"
#include "Highlighter.hpp"
#include "XmlSettings.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QStringList confData, QString confFile);
    ~MainWindow();

    void createMenus();
    void createActions();
    void createActionsFile();
    void createActionsEdit();
    void createActionsSyntax();
    void createActionsLanguages();
    void createActionsTheme();
    void createActionsAbout();

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

    void changeSyntax();
    void changeSyntaxCpp();
    void changeSyntaxCss();
    void changeSyntaxHtml();
    void changeSyntaxJava();
    void changeSyntaxPhp();
    void changeSyntaxPlainText();
    void changeSyntaxPython();
    void changeSyntaxShell();
    void changeSyntaxXml();

private:
    QVBoxLayout *layout;
    Tab *tabWidget;
    FindAndReplaceWidget *findAndReplace;
    QStringList configData; //config data tab
    XmlSettings *settings;
    QMenuBar *mnuBar;
    Highlighter *syntaxHighlighter;

    //actions file
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionPrint;
    QAction *actionQuit;

    //actions edit
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFont;
    QAction *actionZoomMore;
    QAction *actionZoomLess;
    QAction *actionFindAndReplace;

    //actions syntax
    QAction *actionCpp;
    QAction *actionCss;
    QAction *actionHtml;
    QAction *actionJava;
    QAction *actionPhp;
    QAction *actionPlainText;
    QAction *actionPython;
    QAction *actionShell;
    QAction *actionXml;

    //actions languages
    QAction *actionLanguageSystem;
    QAction *actionLanguageFr;
    QAction *actionLanguageEn;

    //actions themes
    QAction *actionThemeLight;
    QAction *actionThemeDark;

    //actions about
    QAction *actionAbout;
    QAction *actionAboutQt;

};

#endif // MainWindow

