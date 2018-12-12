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

#include "MainWindow.hpp"

MainWindow::MainWindow(QStringList confData, QString confFile)
{
    settings = new XmlSettings(confFile);
    configData = confData;
    QFont font = QFont(configData[0],configData[1].toInt());
    QString lang = configData[2];
    QString theme = configData[3];

    tabWidget = new Tab(this,font);

    findAndReplace = new FindAndReplaceWidget(this);
    findAndReplace->hide();

    syntaxHighlighter = new Highlighter();

    //layout init
    layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->addWidget(tabWidget);
    layout->addWidget(findAndReplace);


    //window init
    setMinimumSize(200,45);
    resize(700,400);
    QWidget *cWidget = new QWidget(this);
    cWidget->setLayout(layout);
    setCentralWidget(cWidget);
    setWindowIcon(QIcon(":/icons/icon.ico"));
    setAcceptDrops(true);

    //init menu bar
    mnuBar = new QMenuBar(this);
    setMenuBar(mnuBar);

    // init action and menus
    createActions();
    createMenus();

    if(lang == "System")
    {
        actionLanguageSystem->setChecked(true);
    }
    else if(lang == "Fr")
    {
        actionLanguageFr->setChecked(true);
    }
    else if(lang == "En")
    {
        actionLanguageEn->setChecked(true);
    }

    if(theme == "Light")
    {
        actionThemeLight->setChecked(true);
    }
    else if(theme == "Dark")
    {
        actionThemeDark->setChecked(true);
    }



    //get files if Open with ...
    if(QCoreApplication::arguments().size() > 1)
    {
        for(int i=1; i<QCoreApplication::arguments().size(); i++)
        {
            tabWidget->addNewTab(QCoreApplication::arguments().at(i));
        }
    }
    else
    {
        newFile();
    }

    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeWindowTitle()));

    //transmit findAndReplace signals to tabWidget
    connect(findAndReplace, SIGNAL(findString(QString)), tabWidget, SLOT(findString(QString)));
    connect(findAndReplace, SIGNAL(findAllStrings(QString)), tabWidget, SLOT(findAllStrings(QString)));
    connect(findAndReplace, SIGNAL(replace(QString,QString)), tabWidget, SLOT(replace(QString,QString)));
    connect(findAndReplace, SIGNAL(replaceAll(QString,QString)), tabWidget, SLOT(replaceAll(QString,QString)));
    changeWindowTitle();
}

MainWindow::~MainWindow()
{
    delete settings;
    delete syntaxHighlighter;
}

void MainWindow::createActions()
{

    /* create actions:
     * - init action
     * - add shortcut
     * - connect to slot
     */

    createActionsFile();
    createActionsEdit();
    createActionsSyntax();
    createActionsLanguages();
    createActionsTheme();
    createActionsAbout();
}

void MainWindow::createActionsFile()
{
    actionNew = new QAction(tr("New File"), this);
    actionNew->setShortcut(QKeySequence::New);
    connect(actionNew, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    actionOpen = new QAction(tr("Open File ..."), this);
    actionOpen->setShortcut(QKeySequence::Open);
    connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()));

    actionSave = new QAction(tr("Save"), this);
    actionSave->setShortcut(QKeySequence::Save);
    connect(actionSave, SIGNAL(triggered(bool)), tabWidget, SLOT(save()));

    actionSaveAs = new QAction(tr("Save As ..."), this);
    actionSaveAs->setShortcut(QKeySequence("Ctrl+Maj+S"));
    connect(actionSaveAs, SIGNAL(triggered(bool)), tabWidget, SLOT(saveAs()));

    actionPrint = new QAction(tr("Print ..."), this);
    actionPrint->setShortcut(QKeySequence::Print);
    connect(actionPrint, SIGNAL(triggered(bool)), tabWidget, SLOT(printFile()));

    actionQuit = new QAction(tr("Quit"), this);
    actionQuit->setShortcut(QKeySequence::Quit);
    connect(actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));
}

void MainWindow::createActionsEdit()
{
    actionUndo = new QAction(tr("Undo"), this);
    actionUndo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    connect(actionUndo, SIGNAL(triggered(bool)), tabWidget , SLOT(undo()));

    actionRedo = new QAction(tr("Redo"), this);
    actionRedo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    connect(actionRedo, SIGNAL(triggered(bool)), tabWidget, SLOT(redo()));

    actionCut = new QAction(tr("Cut"), this);
    actionCut->setShortcut(QKeySequence::Cut);
    connect(actionCut, SIGNAL(triggered(bool)), tabWidget, SLOT(cut()));

    actionCopy = new QAction(tr("Copy"), this);
    actionCopy->setShortcut(QKeySequence::Copy);
    connect(actionCopy, SIGNAL(triggered(bool)), tabWidget, SLOT(copy()));

    actionPaste = new QAction(tr("Paste"), this);
    actionPaste->setShortcut(QKeySequence::Paste);
    connect(actionPaste, SIGNAL(triggered(bool)), tabWidget, SLOT(paste()));

    actionFont = new QAction(tr("Font ..."), this);
    connect(actionFont, SIGNAL(triggered(bool)), this, SLOT(changeFont()));

    actionZoomMore = new QAction(tr("Zoom in"),this);
    actionZoomMore->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
    connect(actionZoomMore, SIGNAL(triggered(bool)), this, SLOT(zoomIn()));

    actionZoomLess = new QAction(tr("Zoom out"),this);
    actionZoomLess->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    connect(actionZoomLess, SIGNAL(triggered(bool)), this, SLOT(zoomOut()));

    actionFindAndReplace = new QAction(tr("Find And Replace"), this);
    actionFindAndReplace->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    connect(actionFindAndReplace, SIGNAL(triggered(bool)), findAndReplace, SLOT(show()));
}

void MainWindow::createActionsSyntax()
{
    actionCpp = new QAction("C++", this);
    actionCpp->setCheckable(true);
    connect(actionCpp, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxCpp()));

    actionCss = new QAction("CSS", this);
    actionCss->setCheckable(true);
    actionCss->setDisabled(true);
    connect(actionCss, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxCss()));

    actionHtml = new QAction("HTML", this);
    actionHtml->setCheckable(true);
    actionHtml->setDisabled(true);
    connect(actionHtml, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxHtml()));

    actionJava = new QAction("Java", this);
    actionJava->setCheckable(true);
    actionJava->setDisabled(true);
    connect(actionJava, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxJava()));

    actionPhp = new QAction("PHP", this);
    actionPhp->setCheckable(true);
    actionPhp->setDisabled(true);
    connect(actionPhp, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxPhp()));

    actionPlainText = new QAction("Plain Text", this);
    actionPlainText->setCheckable(true);
    actionPlainText->setChecked(true);
    connect(actionPlainText, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxPlainText()));

    actionPython = new QAction("Python", this);
    actionPython->setCheckable(true);
    connect(actionPython, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxPython()));

    actionShell = new QAction("Shell Script", this);
    actionShell->setCheckable(true);
    actionShell->setDisabled(true);
    connect(actionShell, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxShell()));

    actionXml = new QAction("XML", this);
    actionXml->setCheckable(true);
    actionXml->setDisabled(true);
    connect(actionXml, SIGNAL(triggered(bool)), this, SLOT(changeSyntaxXml()));
}

void MainWindow::createActionsLanguages()
{
    actionLanguageSystem = new QAction(tr("System Language"), this);
    actionLanguageSystem->setCheckable(true);
    connect(actionLanguageSystem, SIGNAL(triggered(bool)), this, SLOT(changeLanguageSystem()));

    actionLanguageFr = new QAction(tr("French"), this);
    actionLanguageFr->setCheckable(true);
    connect(actionLanguageFr, SIGNAL(triggered(bool)), this, SLOT(changeLanguageFr()));

    actionLanguageEn = new QAction(tr("English"), this);
    actionLanguageEn->setCheckable(true);
    connect(actionLanguageEn, SIGNAL(triggered(bool)), this, SLOT(changeLanguageEn()));
}

void MainWindow::createActionsTheme()
{
    actionThemeLight = new QAction(tr("Light"), this);
    actionThemeLight->setCheckable(true);
    connect(actionThemeLight, SIGNAL(triggered(bool)), this, SLOT(changeThemeLight()));

    actionThemeDark = new QAction(tr("Dark"), this);
    actionThemeDark->setCheckable(true);
    connect(actionThemeDark, SIGNAL(triggered(bool)), this, SLOT(changeThemeDark()));
}

void MainWindow::createActionsAbout()
{
    actionAbout = new QAction(tr("About ..."), this);
    actionAbout->setShortcut(QKeySequence::HelpContents);
    connect(actionAbout, SIGNAL(triggered(bool)), this, SLOT(about()));

    actionAboutQt = new QAction(tr("About Qt..."), this);
    connect(actionAboutQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    mnuBar->setCursor(Qt::PointingHandCursor);

    QMenu *fileMenu = mnuBar->addMenu(tr("&File"));
    fileMenu->setCursor(Qt::PointingHandCursor);
    fileMenu->addAction(actionNew);
    fileMenu->addAction(actionOpen);
    fileMenu->addAction(actionSave);
    fileMenu->addAction(actionSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(actionPrint);
    fileMenu->addSeparator();
    fileMenu->addAction(actionQuit);

    QMenu *editMenu = mnuBar->addMenu(tr("&Edit"));
    editMenu->setCursor(Qt::PointingHandCursor);
    editMenu->addAction(actionUndo);
    editMenu->addAction(actionRedo);
    editMenu->addSeparator();
    editMenu->addAction(actionCut);
    editMenu->addAction(actionCopy);
    editMenu->addAction(actionPaste);
    editMenu->addSeparator();
    editMenu->addAction(actionFont);
    editMenu->addSeparator();
    editMenu->addAction(actionZoomMore);
    editMenu->addAction(actionZoomLess);
    editMenu->addSeparator();
    editMenu->addAction(actionFindAndReplace);

    QMenu *syntaxMenu = mnuBar->addMenu(tr("&Syntax (WIP)"));
    syntaxMenu->setCursor(Qt::PointingHandCursor);
    syntaxMenu->addAction(actionCpp);
    syntaxMenu->addAction(actionCss);
    syntaxMenu->addAction(actionHtml);
    syntaxMenu->addAction(actionJava);
    syntaxMenu->addAction(actionPhp);
    syntaxMenu->addAction(actionPlainText);
    syntaxMenu->addAction(actionPython);
    syntaxMenu->addAction(actionShell);
    syntaxMenu->addAction(actionXml);

    QMenu *languagesMenu = mnuBar->addMenu(tr("&Languages"));
    languagesMenu->setCursor(Qt::PointingHandCursor);
    languagesMenu->addAction(actionLanguageSystem);
    languagesMenu->addAction(actionLanguageFr);
    languagesMenu->addAction(actionLanguageEn);

    QMenu *themeMenu = mnuBar->addMenu(tr("&Themes"));
    themeMenu->setCursor((Qt::PointingHandCursor));
    themeMenu->addAction(actionThemeLight);
    themeMenu->addAction(actionThemeDark);

    QMenu *aboutMenu = mnuBar->addMenu(tr("&?"));
    aboutMenu->setCursor(Qt::PointingHandCursor);
    aboutMenu->addAction(actionAbout);
    aboutMenu->addAction(actionAboutQt);
}

void MainWindow::about()
{
    QMessageBox::information(this, tr("About"), QString(tr("Text editor released by Mix<br />Sorry for English mistakes, I don't speak English very well :/ ")
                                                        + "<br /><strong>" + tr("Release number") + ": 4.2-dev</strong>"
                                                        + "<br /><br />" + tr("Software distributed under GPLv3 license")
                                                        + "<br /> <a href=\"https://www.gnu.org/licenses/\">https://www.gnu.org/licenses/</a>"));
}

void MainWindow::open()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tabWidget->getCurrentEditor()->getFileTypes());


    if(!filePath.isEmpty()) //test if dialog cancelled
    {
        newFile(filePath);
    }

}

void MainWindow::changeFont()
{
    bool ok = false;


        QFont newFont = QFontDialog::getFont(&ok, tabWidget->getFont(), this, tr("Choose a font"));

        if (ok)
        {
            tabWidget->setFont(newFont);
        }
        //write new config
        configData[0] = newFont.family();
        configData[1] = QString::number(newFont.pointSize());

}

void MainWindow::changeWindowTitle()
{
    setWindowTitle(tabWidget->getTitle(false, tabWidget->getCurrentEditor()->getFilePath())[1] + " - " + tr("QMText"));
}

void MainWindow::closeEvent(QCloseEvent * event) //save files before quit
{
    bool cancel = false;

    for(int i=0; i<tabWidget->count();i++)
    {
        tabWidget->setCurrentIndex(i);
        if(tabWidget->getCurrentEditor()->document()->isModified())
        {
            switch (tabWidget->saveMessageBox())
            {
                case QMessageBox::Save:
                    tabWidget->save();
                    break;
                case QMessageBox::Discard:
                    break;
                case QMessageBox::Cancel:
                    cancel=true;
                    break;
                default:
                     //can't go here
                     break;
            }
        }
        if(cancel)
            break;
    }

    if(cancel)
    {
        event->ignore();
    }
    else
    {
        settings->write(configData);
        QWidget::closeEvent(event); //close soft
    }
}

void MainWindow::newFile(QString path)
{
    tabWidget->addNewTab(path);

    //if code file, choose right highlightning
    if(path.endsWith(".cpp") || path.endsWith(".c") || path.endsWith(".cc") || path.endsWith(".cxx") || path.endsWith(".c++") || path.endsWith(".hpp") || path.endsWith(".h") || path.endsWith(".hpp") || path.endsWith(".hh") || path.endsWith(".hxx") || path.endsWith(".h++"))
        changeSyntaxCpp();
    else if(path.endsWith(".css"))
        changeSyntaxCss();
    else if(path.endsWith(".html") || path.endsWith(".htm") || path.endsWith(".xhtml") || path.endsWith(".jhtml"))
        changeSyntaxHtml();
    else if(path.endsWith(".java") || path.endsWith(".class"))
        changeSyntaxJava();
    else if(path.endsWith(".php") || path.endsWith(".php4") || path.endsWith(".php3") || path.endsWith(".phtml"))
        changeSyntaxPhp();
    else if(path.endsWith(".py") || path.endsWith(".pyc") || path.endsWith(".pyd") || path.endsWith(".pyo") || path.endsWith(".pyw") || path.endsWith(".pyz"))
        changeSyntaxPython();
    else if(path.endsWith(".sh"))
        changeSyntaxShell();
    else if(path.endsWith(".xml") || path.endsWith(".rss") || path.endsWith(".svg"))
        changeSyntaxXml();
}

void MainWindow::dropEvent(QDropEvent *event) // drop
{
    QString filePath = event->mimeData()->urls().at(0).toString().right(event->mimeData()->urls().at(0).toString().size()-7);
    event->accept();
    #ifdef WIN32 //change path format for windows
    filePath.replace("/", "\\"); // change "/" to "\"
    #endif
    newFile(filePath);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) // drag
{
    if(event->mimeData()->hasUrls())
            event->acceptProposedAction();
}

void MainWindow::changeLanguage(QString language) // change language config
{
    configData[2] = language;

    QMessageBox::information(this, tr("Reboot needed"), tr("The language change will take effect after QMText's next reboot."));
}

//action to change language
void MainWindow::changeLanguageSystem()
{
    changeLanguage("System");
    actionLanguageEn->setChecked(false);
    actionLanguageFr->setChecked(false);
    actionLanguageSystem->setChecked(true);
}

void MainWindow::changeLanguageFr()
{
    changeLanguage("Fr");
    actionLanguageEn->setChecked(false);
    actionLanguageFr->setChecked(true);
    actionLanguageSystem->setChecked(false);
}

void MainWindow::changeLanguageEn()
{
    changeLanguage("En");
    actionLanguageEn->setChecked(true);
    actionLanguageFr->setChecked(false);
    actionLanguageSystem->setChecked(false);
}

void MainWindow::changeTheme(QString theme) // change theme config
{
    configData[3] = theme;

    QMessageBox::information(this, tr("Reboot needed"), tr("The theme change will take effect after QMText's next reboot."));
}

//action to change theme
void MainWindow::changeThemeLight()
{
    changeTheme("Light");
    actionThemeDark->setChecked(false);
    actionThemeLight->setChecked(true);
}

void MainWindow::changeThemeDark()
{
    changeTheme("Dark");
    actionThemeDark->setChecked(true);
    actionThemeLight->setChecked(false);
}

//zoom actions
void MainWindow::zoomIn()
{
    QFont font = tabWidget->getFont();
    font.setPointSize(font.pointSize()+1);
    tabWidget->setFont(font);
    configData[1] = QString::number(tabWidget->getFont().pointSize());
}

void MainWindow::zoomOut()
{
    QFont font = tabWidget->getFont();
    font.setPointSize(font.pointSize()-1);
    tabWidget->setFont(font);
    configData[1] = QString::number(tabWidget->getFont().pointSize());
}

void MainWindow::changeSyntax()
{
    actionCpp->setChecked(false);
    actionCss->setChecked(false);
    actionHtml->setChecked(false);
    actionJava->setChecked(false);
    actionPhp->setChecked(false);
    actionPlainText->setChecked(false);
    actionPython->setChecked(false);
    actionShell->setChecked(false);
    actionXml->setChecked(false);

    QString type = tabWidget->getCurrentEditor()->getSyntax();

    if(type == "cpp")
        actionCpp->setChecked(true);
    else if(type == "css")
        actionCss->setChecked(true);
    else if(type == "html")
        actionHtml->setChecked(true);
    else if(type == "java")
        actionJava->setChecked(true);
    else if(type == "php")
        actionPhp->setChecked(true);
    else if(type == "plain")
        actionPlainText->setChecked(true);
    else if(type == "python")
        actionPython->setChecked(true);
    else if(type == "shell")
        actionShell->setChecked(true);
    else if(type == "xml")
        actionXml->setChecked(true);
    else
        actionPlainText->setChecked(true);

    syntaxHighlighter->changeHighlighter(type, tabWidget->getCurrentEditor()->document());
}

void MainWindow::changeSyntaxCpp()
{
    tabWidget->getCurrentEditor()->setSyntax("cpp");
    changeSyntax();
}

void MainWindow::changeSyntaxCss()
{
    tabWidget->getCurrentEditor()->setSyntax("css");
    changeSyntax();
}

void MainWindow::changeSyntaxHtml()
{
    tabWidget->getCurrentEditor()->setSyntax("html");
    changeSyntax();
}

void MainWindow::changeSyntaxJava()
{
    tabWidget->getCurrentEditor()->setSyntax("java");
    changeSyntax();
}

void MainWindow::changeSyntaxPhp()
{
    tabWidget->getCurrentEditor()->setSyntax("php");
    changeSyntax();
}

void MainWindow::changeSyntaxPlainText()
{
    tabWidget->getCurrentEditor()->setSyntax("plain");
    changeSyntax();
}

void MainWindow::changeSyntaxPython()
{
    tabWidget->getCurrentEditor()->setSyntax("python");
    changeSyntax();
}

void MainWindow::changeSyntaxShell()
{
    tabWidget->getCurrentEditor()->setSyntax("shell");
    changeSyntax();
}

void MainWindow::changeSyntaxXml()
{
    tabWidget->getCurrentEditor()->setSyntax("xml");
    changeSyntax();
}
