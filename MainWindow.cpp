#include "MainWindow.hpp"

MainWindow::MainWindow(QString confFile, QFont font, QString lang, QString theme)
{
    configFile = confFile;
    QFile conf(configFile);
    QTextStream fluxConf(&conf);
    fluxConf.setCodec("UTF-8");
    conf.open(QIODevice::ReadWrite | QIODevice::Text);
    while(!fluxConf.atEnd())
    {
        confData.append(fluxConf.readLine());
    }

    tabWidget = new Tab(this,font);

    findAndReplace = new FindAndReplaceWidget(this);
    findAndReplace->hide();

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

void MainWindow::createActions()
{

    /* create actions:
     * - init action
     * - add shortcut
     * - connect to slot
     */

    actionNew = new QAction(tr("New File"), this);
    actionNew->setShortcut(QKeySequence::New);
    connect(actionNew, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    actionAbout = new QAction(tr("About ..."), this);
    actionAbout->setShortcut(QKeySequence::HelpContents);
    connect(actionAbout, SIGNAL(triggered(bool)), this, SLOT(about()));

    actionAboutQt = new QAction(tr("About Qt..."), this);
    connect(actionAboutQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    actionSave = new QAction(tr("Save"), this);
    actionSave->setShortcut(QKeySequence::Save);
    connect(actionSave, SIGNAL(triggered(bool)), tabWidget, SLOT(save()));

    actionSaveAs = new QAction(tr("Save As ..."), this);
    actionSaveAs->setShortcut(QKeySequence("Ctrl+Maj+S"));
    connect(actionSaveAs, SIGNAL(triggered(bool)), tabWidget, SLOT(saveAs()));

    actionUndo = new QAction(tr("Undo"), this);
    actionUndo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    connect(actionUndo, SIGNAL(triggered(bool)), tabWidget , SLOT(undo()));

    actionRedo = new QAction(tr("Redo"), this);
    actionRedo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    connect(actionRedo, SIGNAL(triggered(bool)), tabWidget, SLOT(redo()));

    actionCopy = new QAction(tr("Copy"), this);
    actionCopy->setShortcut(QKeySequence::Copy);
    connect(actionCopy, SIGNAL(triggered(bool)), tabWidget, SLOT(copy()));

    actionPaste = new QAction(tr("Paste"), this);
    actionPaste->setShortcut(QKeySequence::Paste);
    connect(actionPaste, SIGNAL(triggered(bool)), tabWidget, SLOT(paste()));

    actionCut = new QAction(tr("Cut"), this);
    actionCut->setShortcut(QKeySequence::Cut);
    connect(actionCut, SIGNAL(triggered(bool)), tabWidget, SLOT(cut()));

    actionOpen = new QAction(tr("Open File ..."), this);
    actionOpen->setShortcut(QKeySequence::Open);
    connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()));

    actionFont = new QAction(tr("Font ..."), this);
    connect(actionFont, SIGNAL(triggered(bool)), this, SLOT(changeFont()));

    actionPrint = new QAction(tr("Print ..."), this);
    actionPrint->setShortcut(QKeySequence::Print);
    connect(actionPrint, SIGNAL(triggered(bool)), tabWidget, SLOT(printFile()));

    actionZoomMore = new QAction(tr("Zoom in"),this);
    actionZoomMore->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
    connect(actionZoomMore, SIGNAL(triggered(bool)), this, SLOT(zoomIn()));

    actionZoomLess = new QAction(tr("Zoom out"),this);
    actionZoomLess->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    connect(actionZoomLess, SIGNAL(triggered(bool)), this, SLOT(zoomOut()));

    actionFindAndReplace = new QAction(tr("Find And Replace"), this);
    actionFindAndReplace->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    connect(actionFindAndReplace, SIGNAL(triggered(bool)), findAndReplace, SLOT(show()));

    actionLanguageSystem = new QAction(tr("System Language"), this);
    actionLanguageSystem->setCheckable(true);
    connect(actionLanguageSystem, SIGNAL(triggered(bool)), this, SLOT(changeLanguageSystem()));

    actionLanguageFr = new QAction(tr("French"), this);
    actionLanguageFr->setCheckable(true);
    connect(actionLanguageFr, SIGNAL(triggered(bool)), this, SLOT(changeLanguageFr()));

    actionLanguageEn = new QAction(tr("English"), this);
    actionLanguageEn->setCheckable(true);
    connect(actionLanguageEn, SIGNAL(triggered(bool)), this, SLOT(changeLanguageEn()));

    actionThemeLight = new QAction(tr("Light"), this);
    actionThemeLight->setCheckable(true);
    connect(actionThemeLight, SIGNAL(triggered(bool)), this, SLOT(changeThemeLight()));

    actionThemeDark = new QAction(tr("Dark"), this);
    actionThemeDark->setCheckable(true);
    connect(actionThemeDark, SIGNAL(triggered(bool)), this, SLOT(changeThemeDark()));

}

void MainWindow::createMenus()
{
    mnuBar->setCursor(Qt::PointingHandCursor);


    QMenu *fichier = mnuBar->addMenu(tr("&File"));
    fichier->setCursor(Qt::PointingHandCursor);
    fichier->addAction(actionNew);
    fichier->addAction(actionOpen);
    fichier->addAction(actionSave);
    fichier->addAction(actionSaveAs);
    fichier->addSeparator();
    fichier->addAction(actionPrint);

    QMenu *edition = mnuBar->addMenu(tr("&Edit"));
    edition->setCursor(Qt::PointingHandCursor);
    edition->addAction(actionUndo);
    edition->addAction(actionRedo);
    edition->addSeparator();
    edition->addAction(actionCut);
    edition->addAction(actionCopy);
    edition->addAction(actionPaste);
    edition->addSeparator();
    edition->addAction(actionFont);
    edition->addSeparator();
    edition->addAction(actionZoomMore);
    edition->addAction(actionZoomLess);
    edition->addSeparator();
    edition->addAction(actionFindAndReplace);

    QMenu *langues = mnuBar->addMenu(tr("&Languages"));
    langues->setCursor(Qt::PointingHandCursor);
    langues->addAction(actionLanguageSystem);
    langues->addAction(actionLanguageFr);
    langues->addAction(actionLanguageEn);

    QMenu *theme = mnuBar->addMenu(tr("&Themes"));
    theme->setCursor((Qt::PointingHandCursor));
    theme->addAction(actionThemeLight);
    theme->addAction(actionThemeDark);

    QMenu *aide = mnuBar->addMenu(tr("&?"));
    aide->setCursor(Qt::PointingHandCursor);
    aide->addAction(actionAbout);
    aide->addAction(actionAboutQt);
}

void MainWindow::about()
{
    QMessageBox::information(this, tr("About"), QString(tr("Text editor released by Mix<br />Sorry for English mistakes, I don't speak English very well :/ ") + "<br /><strong>" + tr("Release number") + ": 4.2-dev</strong>"));
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
        confData[0] = "Font = \"" + newFont.family() + "\"";
        confData[1] = "FontSize = \"" + QString::number(newFont.pointSize()) + "\"";

}

void MainWindow::changeWindowTitle()
{
    setWindowTitle(tabWidget->getTitle(false, tabWidget->getCurrentEditor()->getFilePath())[1] + " - " + tr("QMText"));
}

void MainWindow::closeEvent(QCloseEvent * event) //save files before quit
{
    bool cancel = false;
    //open config file
    QFile conf(configFile);
    QTextStream fluxConf(&conf);
    fluxConf.setCodec("UTF-8");
    conf.open(QIODevice::ReadWrite | QIODevice::Text);

    for(int i=0; i<tabWidget->count();i++)
    {
        tabWidget->setCurrentIndex(i);
        if(!tabWidget->getCurrentEditor()->getSaveState())
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
        conf.resize(0); // erase config file
        fluxConf << confData[0] << endl << confData[1] << endl << confData[2] << endl << confData[3]; // write new config
        conf.close(); // close file
        QWidget::closeEvent(event); //close soft
    }
}

void MainWindow::newFile(QString path)
{
    tabWidget->addNewTab(path);
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

void MainWindow::changeLanguage(QString langue) // change language config
{
    confData[2] = "Language = \"" + langue + "\"";

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
    confData[3] = "Theme = \"" + theme + "\"";

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
    confData[1] = "FontSize = \"" + QString::number(tabWidget->getFont().pointSize()) + "\"";
}

void MainWindow::zoomOut()
{
    QFont font = tabWidget->getFont();
    font.setPointSize(font.pointSize()-1);
    tabWidget->setFont(font);
    confData[1] = "FontSize = \"" + QString::number(tabWidget->getFont().pointSize()) + "\"";
}
